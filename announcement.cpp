#include "db.h"

void searching::announcement()
{
    sqlite3 *db; //핸들, 파일디스크립터같은
    char *err_msg = 0; // 오류메시지

    int rc = sqlite3_open("/home/aiot11/Downloads/worknet", &db); //db 열기

    if (rc != SQLITE_OK) // 오픈에러
    {
        fprintf(stderr, "Cannot open database: %s\n", 
                sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    std::string random_announcement = "SELECT 회사명, 경력, 학력, 필요스킬, 고용형태, 기업형태 FROM resume ORDER BY RANDOM() LIMIT 2;";

    rc = sqlite3_exec(db, random_announcement.c_str(), callback, 0, &err_msg); //쿼리문 전달 및 실행
    if(rc != SQLITE_OK)
    {
        std::cout << "error" << std::endl;
        exit(1);
    }
    sqlite3_close(db); //DB 닫기
}