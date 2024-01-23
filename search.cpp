#include "db.h"

void searching::search()
{
    system("clear");
    int choice = 0;
    while(choice <= 3)
    {
        std::cout << "============================" << std::endl;
        std::cout << "          1. 검색" << std::endl;
        std::cout << "        2. 상세검색" << std::endl;
        std::cout << "       3. 메인페이지" << std::endl;
        std::cout << "============================" << std::endl;
        std::cout << "선택:";
        std::cin >> choice;
        if(choice == 1)
        {
            system("clear");
            std::cout << "============================================" << std::endl;
            announcement(); //랜덤공고 보여주기용
            std::cout << "============================================" << std::endl;
            sqlite3 *db; //핸들, 파일디스크립터같은
            char *err_msg = 0; // 오류메시지
            sqlite3_stmt* res;

            //db 열고 입력값이랑 db저장된 갑이랑 비교하고 공고 출력해주기
            std::cout << "\t검색창" << std::endl;
            std::cout << "키워드를 입력해주세요." << std::endl;
            std::cout << "ex) C++, C, C#" << std::endl;
            std::cin >> user_search;

            int rc = sqlite3_open("/home/aiot11/Downloads/worknet", &db); //db 열기

            if (rc != SQLITE_OK) // 오픈에러
            {
                fprintf(stderr, "Cannot open database: %s\n", 
                        sqlite3_errmsg(db));
                sqlite3_close(db);
                exit(1);
            }
            system("clear");
            std::cout << "\n\n\n\n검색중:";
            std::cout << " /____________________/" << std::endl;
            std::cout << "검색내용:" << user_search << std::endl;
            sleep(1);
            system("clear");
            std::cout << "\n\n\n\n검색중:";
            std::cout << " /#######_____________/" << std::endl;
            std::cout << "검색내용:" << user_search << std::endl;
            sleep(1);
            system("clear");
            std::cout << "\n\n\n\n검색중:";
            std::cout << " /#############_______/" << std::endl;
            std::cout << "검색내용:" << user_search << std::endl;
            sleep(1);
            system("clear");
            std::cout << "\n\n\n\n검색중:";
            std::cout << " /####################/" << std::endl;
            std::cout << "검색내용:" << user_search << std::endl;
            sleep(1);
            system("clear");

            std::string search = "SELECT 회사명, 경력, 학력, 필요스킬, 고용형태, 기업형태 FROM resume WHERE 필요스킬 LIKE '%"+ user_search +"%';";

            std::cout << "============================================" << std::endl;
            rc = sqlite3_exec(db, search.c_str(), callback, 0, &err_msg); //쿼리문 전달 및 실행
            std::cout << "============================================" << std::endl;

            if(search_numbers() == "0")
            {
                std::string buf;
                std::cout << "검색하신 키워드와 일치하는 공고가 없습니다." << std::endl;
                std::cout << "메인페이로 이동을 원하시면 아무키를 입력해주세요." << std::endl;
                std::cout << "입력:";
                std::cin >> buf;
                system("clear");
                break;
            }

            if(rc != SQLITE_OK)
            {
                std::cout << "error" << std::endl;
                exit(1);
            }
    
            //회사공고 들어가기
            std::cout << "공고상세정보 보기를 원하시면 회사명을 입력해주세요" << std::endl;
            std::cout << "검색:";
            std::string ser1;
            // getline(std::cin, ser1);
            std::cin >> ser1;
            while(ser1.size() < 9) //한글은 크기 3
            {
                std::cout << "검색어 입력시 3글자 이상으로 입력해주세요" << std::endl;
                std::cout << "검색:";
                std::cin >> ser1;
            }
            std::string detail_search = "SELECT * FROM details WHERE 회사명 LIKE '%"+ ser1 +"%';";

            system("clear");
            std::cout << "\n\n\n\n검색중:";
            std::cout << " /____________________/" << std::endl;
            std::cout << "검색내용:" << ser1 << std::endl;
            sleep(1);
            system("clear");
            std::cout << "\n\n\n\n검색중:";
            std::cout << " /#######_____________/" << std::endl;
            std::cout << "검색내용:" << ser1 << std::endl;
            sleep(1);
            system("clear");
            std::cout << "\n\n\n\n검색중:";
            std::cout << " /#############_______/" << std::endl;
            std::cout << "검색내용:" << ser1 << std::endl;
            sleep(1);
            system("clear");
            std::cout << "\n\n\n\n검색중:";
            std::cout << " /####################/" << std::endl;
            std::cout << "검색내용:" << ser1 << std::endl;
            sleep(1);
            system("clear");

            std::cout << "====================공고상세정보====================" << std::endl;
            rc = sqlite3_exec(db, detail_search.c_str(), callback, 0, &err_msg); //쿼리문 전달 및 실행
            std::cout << "====================================================" << std::endl;

            //검색건수
            if(rc != SQLITE_OK)
            {
                std::cout << "error" << std::endl;
                exit(1);
            }

            std::string choice;
            std::cout << "1. 기업정보" << std::endl;
            std::cout << "기업정보를 원하시면 1번 또는 ""기업정보""를 입력해주세요." << std::endl;
            std::cin >> choice;

            if(choice == "1" || choice == "기업정보")
            {
                system("clear");
                std::string company_information = "SELECT 회사명, 설립년도, 사원수, 산업, 기업형태 FROM resume WHERE 회사명 LIKE '%"+ ser1 + "%';"; //기업정보 쿼리문
                std::cout << "=============기업상세정보=============" << std::endl;
                std::cout << "기업정보" << std::endl;
                rc = sqlite3_exec(db, company_information.c_str(), callback, 0, &err_msg);
                std::cout << "======================================" << std::endl;
                if(rc != SQLITE_OK)
                {
                    std::cout << "error" << std::endl;
                }
            }
            else
            {
                std::cout << "잘못된 입력입니다. 메인페이지로 돌아갑니다." << std::endl;
                sleep(2);
                system("clear");
                break;
            }
            std::string main_back;
            std::cout << "메인페이지로 이동을 원하시면 아무키나 입력해주세요." << std::endl;
            std::cin >> main_back;
            std::cin.ignore();
            system("clear");
            sqlite3_close(db); //DB 닫기
        }
        else if(choice == 2)
            detail_search();
        else if(choice == 3)
        {
            system("clear");
            break;
        }
        break;
    }
}