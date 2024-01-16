#include <stdio.h>
#include <iostream>
#include <sqlite3.h>
#include <vector>
#include "SQLiteCpp.h"

// public

bool SQLiteCpp::_sqlite3_open(std::string dir)
{
    if (sqlite3_open(dir.c_str(), &db) != SQLITE_OK)
    {
        std::cout << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);

        return false;
    }

    // table check
    if (this->IsTableExist() == false)
    {
        this->CreateTable();
    }

    return true;
}

bool SQLiteCpp::_sqlite3_close()
{
    return (sqlite3_close(db) == SQLITE_OK);
}

std::vector<std::vector<std::string>>  SQLiteCpp::GetAllRecords()
{
    std::vector<std::vector<std::string>> result;
    sqlite3_stmt *stmt;
    const char *sql = QUERY_TABLE_SELECT_ALL.c_str();

    std::cout << sql << std::endl;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
        std::cout << "sqlite3_prepare_v2() Fail" << std::endl;

    while (sqlite3_step(stmt) == SQLITE_ROW) // 수행 성공 SQLITE_DONE, 반환 SELECT 경우 SQLITE_ROW
    {

        std::vector<std::string> temp;
        for (size_t i = 0; i < sqlite3_column_count(stmt); i++) // 결과집합의 컬럼 개수를 반환
        {
            std::string str = (const char*)sqlite3_column_text(stmt, i);
            temp.push_back(str);
        }

        result.push_back(temp);
    }

    sqlite3_reset(stmt);
    sqlite3_finalize(stmt);

    return result;
}

//

bool SQLiteCpp::IsTableExist()
{
    sqlite3_stmt *stmt;
    const char *query = QUERY_TABLE_EXIST.c_str();
    bool result = false;

    sqlite3_prepare_v2(this->db, query, -1, &stmt, NULL);
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        result = true;
    }
    sqlite3_reset(stmt);
    sqlite3_finalize(stmt);

    return result;
}

bool SQLiteCpp::CreateTable()
{
    sqlite3_stmt *stmt;
    const char *query = QUERY_TABLE_CREATE.c_str();
    bool result = true;

    sqlite3_prepare_v2(this->db, query, -1, &stmt, NULL);

    // begin
    this->Begin();
    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        fprintf(stderr, "line %d: %s\n", __LINE__, sqlite3_errmsg(this->db));
        result = false;
    }

    // commit
    this->Commit();

    sqlite3_reset(stmt);
    sqlite3_finalize(stmt);

    return result;
}

bool SQLiteCpp::DropTable()
{
    sqlite3_stmt *stmt;
    const char *query = QUERY_TABLE_DROP.c_str();
    bool result = true;

    sqlite3_prepare_v2(this->db, query, -1, &stmt, NULL);

    // begin
    this->Begin();
    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        fprintf(stderr, "line %d: %s\n", __LINE__, sqlite3_errmsg(this->db));
        result = false;
    }

    // commit
    this->Commit();

    sqlite3_reset(stmt);
    sqlite3_finalize(stmt);

    return result;
}

bool SQLiteCpp::Begin()
{
    sqlite3_stmt *stmt;
    const char *query = QUERY_DB_BEGIN___.c_str();
    bool result = true;

    sqlite3_prepare_v2(this->db, query, -1, &stmt, NULL);
    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        fprintf(stderr, "line %d: %s\n", __LINE__, sqlite3_errmsg(this->db));
        result = false;
    }
    sqlite3_reset(stmt);
    sqlite3_finalize(stmt);

    return result;
}

bool SQLiteCpp::Commit()
{
    sqlite3_stmt *stmt;
    const char *query = QUERY_DB_COMMIT__.c_str();
    bool result = true;

    sqlite3_prepare_v2(this->db, query, -1, &stmt, NULL);
    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        fprintf(stderr, "line %d: %s\n", __LINE__, sqlite3_errmsg(this->db));
        result = false;
    }
    sqlite3_reset(stmt);
    sqlite3_finalize(stmt);

    return result;
}

bool SQLiteCpp::Rollback()
{
    sqlite3_stmt *stmt;
    const char *query = QUERY_DB_ROLLBACK.c_str();
    bool result = true;

    sqlite3_prepare(this->db, query, -1, &stmt, NULL);
    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        fprintf(stderr, "line %d: %s\n", __LINE__, sqlite3_errmsg(this->db));
        result = false;
    }
    sqlite3_reset(stmt);
    sqlite3_finalize(stmt);

    return result;
}