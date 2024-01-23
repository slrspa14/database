#include "db.h"

void log::log_in()
{
    system("clear");
    sqlite3 *db; //핸들, 파일디스크립터같은
    char *err_msg = 0; // 오류메시지
    sqlite3_stmt* res;
    std::string join;
    std::cout << "로그인페이지" << std::endl;
    
    std::string pw;
    int rc = sqlite3_open("/home/aiot11/Downloads/worknet", &db); //열고
    
    while(1)
    {
        std::cout << "ID:";
        std::cin >> log_id;
        std::cout << "PW:";
        std::cin >> log_pw;
        join = "SELECT USER_ID, PW FROM USER_DATA WHERE USER_ID = '"+ log_id +"' AND PW = '"+ log_pw + "';";
        rc = sqlite3_prepare_v2(db, join.c_str(), -1, &res, 0); // 준비        

        // 실행하기
        if(sqlite3_step(res) == SQLITE_ROW) // db랑 사용자 입력이 같다면
        {
            system("clear");
            std::cout << "로그인 되었습니다." << std::endl;
            sleep(2);
            log_count++;
            sqlite3_finalize(res); //SQL 쿼리 핸들 정리
            sqlite3_close(db); //DB 닫기
            system("clear");
            break;
        }
        else
        {
            system("clear");
            std::cout << "일치하는 ID 및 PW가 없습니다." << std::endl;
            std::cout << "다시 입력해주세요." << std::endl;
            continue;
        }
    }
}