#include "db.h"


void join::join_page() // 회원가입 페이지
{
    system("clear");
    sqlite3 *db; //핸들, 파일디스크립터같은
    char *err_msg = 0; // 오류메시지
    sqlite3_stmt* res;

    std::string join;

    std::cout << "회원가입" << std::endl;
    int rc = sqlite3_open("/home/aiot11/Downloads/worknet", &db); //db 열기

    //아이디
    while(1)
    {
        std::cout << "ID:";
        std::cin >> join_id;
        while(1)
        {
            join = "SELECT USER_ID FROM USER_DATA WHERE USER_ID = '"+ join_id + "';"; // 입력한 join_id랑 쿼리문 비교
            rc = sqlite3_prepare_v2(db, join.c_str(), -1, &res, 0); // 준비
            rc = sqlite3_step(res); // 실행하기
            if(rc == SQLITE_ROW) // db랑 사용자 입력이 같다면 중복검사
            {
                system("clear");
                std::cout << "중복된 ID입니다. 다시 입력해주세요" << std::endl;
                std::cout << "ID:";
                std::cin >> join_id;
            }
            else
                break;
        }
        break;
    }

    //비번
    std::cout << "PW(숫자 4자리):";
    std::cin >> join_pw;
    while(join_pw.size()>4 || join_pw.size() <= 3)//4자리 제한
    {
        system("clear");
        std::cout << "잘못된 입력\n숫자 4자리만 입력가능\n다시 입력해주세요." << std::endl;
        std::cout << "PW:";
        std::cin >> join_pw;
    }

    //email
    while(1)
    {
        std::cout << "email:";
        std::cin >> join_email;
        while(1)
        {
            join = "SELECT EMAIL FROM USER_DATA WHERE EMAIL = '"+ join_email + "';";
            rc = sqlite3_prepare_v2(db, join.c_str(), -1, &res, 0);
            rc = sqlite3_step(res);
            if(rc == SQLITE_ROW) // db랑 사용자 입력이 같다면 중복검사
            {
                system("clear");
                std::cout << "중복된 e-mail입니다. 다시 입력해주세요" << std::endl;
                std::cout << "eamil:";
                std::cin >> join_email;
            }
            else
                break;
        }
        break;
    }

    //핸드폰
    while(1)
    {
        std::cout << "HP(-제외 11자리):";
        std::cin >> join_pnum;
        while(join_pnum.size() > 11 || join_pnum.size() <= 10)
        {
            system("clear");
            std::cout << "잘못된입력\n11자리만 입력가능\n-제외\n다시 입력해주세요." << std::endl;
            std::cout << "H.P:";
            std::cin >> join_pnum;
        }
        while(1)
        {
            join = "SELECT PNUM FROM USER_DATA WHERE PNUM = '"+ join_pnum + "';";

            rc = sqlite3_prepare_v2(db, join.c_str(), -1, &res, 0);
            rc = sqlite3_step(res);

            if(rc == SQLITE_ROW) // db랑 사용자 입력이 같다면 중복검사
            {
                system("clear");
                std::cout << "중복된 핸드폰번호입니다. 다시 입력해주세요" << std::endl;
                std::cout << "H.P:";
                std::cin >> join_pnum;
            }
            else
                break;
        }
        break;
    }
    join = "INSERT INTO USER_DATA(USER_ID, PW, EMAIL, PNUM) VALUES('"+ join_id +"','"+ join_pw +"','"+ join_email +"','"+ join_pnum +"');"; //쿼리문 보내고
    rc = sqlite3_prepare_v2(db, join.c_str(), -1, &res, 0);// 준비
    rc = sqlite3_step(res); // 실행

    sqlite3_finalize(res); //SQL 쿼리 핸들 정리
    
    sqlite3_close(db); //DB 닫기

    system("clear");
    std::cout << "============================" << std::endl;
    std::cout << "회원가입이 완료되었습니다." << std::endl;
    // std::cout << "회원가입내역" << std::endl;
    std::cout << "ID : " << join_id << std::endl;
    std::cout << "PW : " << join_pw << std::endl;
    std::cout << "e-mail : " <<join_email << std::endl;
    std::cout << "PNUM : " << join_pnum << std::endl;
    std::cout << "============================" << std::endl;
    sleep(3);
    system("clear");
}