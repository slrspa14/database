#pragma once

#include <iostream>
#include <sqlite3.h>
#include <vector>

static const std::string DIR = "/home/aiot11/db.db";
static const std::string QUERY_TABLE_CREATE = "CREATE TABLE Members (code INTEGER PRIMARY KEY AUTOINCREMENT, id TEXT(12), pw TEXT(18), fname TEXT, lname TEXT, ph TEXT, email TEXT, disabled NUMERIC);";
static const std::string QUERY_TABLE_EXIST = "SELECT name FROM sqlite_master WHERE type='table' AND name='Members';";
static const std::string QUERY_TABLE_DROP = "DROP TABLE IF EXISTS Members;";
static const std::string QUERY_TABLE_EXIST_RECORD = "SELECT FilePath FROM Members WHERE FilePath=? AND CheckSum=? AND Version=?;";
static const std::string QUERY_TABLE_DELETE_RECORD = "DELETE FROM Members WHERE FilePath=?;";
static const std::string QUERY_TABLE_INSERT_RECORD = "INSERT INTO Members VALUES(?, ?, ?);";
static const std::string QUERY_TABLE_SELECT_ALL = "SELECT * FROM Members;";
static const std::string QUERY_DB_CLEAN_UP = "VACUUM;";
static const std::string QUERY_DB_BEGIN___ = "BEGIN;";
static const std::string QUERY_DB_COMMIT__ = "COMMIT;";
static const std::string QUERY_DB_ROLLBACK = "ROLLBACK;";

class SQLiteCpp
{
private:
    sqlite3 *db;

private:
    bool CreateTable();
    bool DropTable();
    bool IsTableExist();

    bool Begin();
    bool Commit();
    bool Rollback();

public:
    bool _sqlite3_open(std::string dbName);
    bool _sqlite3_close();
    std::vector<std::vector<std::string>>  GetAllRecords();
    // bool _insert(std::string dir, std::string checksum, void *binaryData, int size);
    // bool _delete(std::string key);

};