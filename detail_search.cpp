#include "db.h"

void searching::detail_search()//상세검색
{
    system("clear");
    while(1)
    {
        sqlite3 *db; //핸들, 파일디스크립터같은
        char *err_msg = 0; // 오류메시지

        int rc = sqlite3_open("/home/aiot11/Downloads/worknet", &db); //db 열기
        
        std::cout << "======지역======" << std::endl;
        std::cout << "      서울" << std::endl;
        std::cout << "      경기" << std::endl;
        std::cout << "      대전" << std::endl;
        std::cout << "      부산" << std::endl;
        std::cout << "      광주" << std::endl;
        std::cout << "      대구" << std::endl;
        std::cout << "      인천" << std::endl;
        std::cout << "      울산" << std::endl;
        std::cout << "===============" << std::endl;
        std::cin >> region;
        system("clear");
        
        std::cout << "=====경력=====" << std::endl;
        std::cout << "     신입" << std::endl;
        std::cout << "     경력" << std::endl;
        std::cout << "==============" << std::endl;
        std::cin >> career;
        system("clear");

        std::cout << "========학력========" << std::endl;
        std::cout << "      학력무관" << std::endl;
        std::cout << "        고졸" << std::endl;
        std::cout << "     초대졸이상" << std::endl;
        std::cout << "   대졸(4년제이상)" << std::endl;
        std::cout << "====================" << std::endl;
        std::cin >> education;
        system("clear");

        std::cout << "\n\n\n\n검색중:";
        std::cout << " /____________________/" << std::endl;
        std::cout << "검색내용:" << region << ", " << career << ", " << education << std::endl;
        sleep(1);
        system("clear");
        std::cout << "\n\n\n검색중:";
        std::cout << " /#######_____________/" << std::endl;
        std::cout << "검색내용:" << region << ", " << career << ", " << education << std::endl;
        sleep(1);
        system("clear");
        std::cout << "\n\n\n검색중:";
        std::cout << " /#############_______/" << std::endl;
        std::cout << "검색내용:" << region << ", " << career << ", " << education << std::endl;
        sleep(1);
        system("clear");
        std::cout << "\n\n\n검색중:";
        std::cout << " /####################/" << std::endl;
        std::cout << "검색내용:" << region << ", " << career << ", " << education << std::endl;
        sleep(1);
        system("clear");
        
        sqlite3_stmt* res;
        std::string  search3 = "SELECT * FROM resume WHERE 근무지역 LIKE '%"+ region +"%' AND 경력 LIKE '%"+ career +"%' AND 학력 LIKE '%"+ education +"%';";
        // std::string com_num = "SELECT 회사명 FROM resume WHERE 근무지역 LIKE '%"+ region +"%' AND 경력 LIKE '%"+ career +"%' AND 학력 LIKE '%"+ education +"%';";
        // sqlite3_prepare_v2(db, com_num.c_str(), -1, &res, 0); // 회사코드용
        // rc = sqlite3_step(res);
        // if(rc == SQLITE_OK) // 회사이름용 //회사코드로 바꾸고
        // {
        //     company_code.push_back(reinterpret_cast<const char*>(sqlite3_column_text(res,0))); // 벡터에 회사코드 저장
        // }

        std::cout << "============================================" << std::endl;
        rc = sqlite3_exec(db, search3.c_str(), callback, 0, &err_msg); //상세검색 출력
        std::cout << "============================================" << std::endl;

        if(search_numbers1() == "0")
        {
            std::string buf;
            std::cout << "검색하신 키워드와 일치하는 공고가 없습니다." << std::endl;
            std::cout << "메인페이지로 이동을 원하시면 아무키를 입력해주세요." << std::endl;
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

        //상세검색 들어가서 회사공고 들어가기
        std::string detail_company_name;
        std::cout << "공고상세정보 보기를 원하시면 회사명을 입력해주세요" << std::endl;
        std::cout << "선택:";
        std::cin >> detail_company_name;
        while(detail_company_name.size() < 9) //한글은 크기 3
        {
            std::cout << "검색어 입력시 3글자 이상으로 입력해주세요" << std::endl;
            std::cout << "검색:";
            std::cin >> detail_company_name;
        }

        // if(company_code.size() > 0) //회사 코드로 바꾸고
        // {
        //     std::cout << ""
        // }

        std::string detail_announcement = "SELECT * FROM details WHERE 회사명 LIKE '%"+ detail_company_name + "%';";
        
        system("clear");
        std::cout << "\n\n\n\n검색중:";
        std::cout << " /____________________/" << std::endl;
        std::cout << "검색내용:"<< detail_company_name << std::endl;
        sleep(1);
        system("clear");
        std::cout << "\n\n\n검색중:";
        std::cout << " /#######_____________/" << std::endl;
        std::cout << "검색내용:"<< detail_company_name << std::endl;
        sleep(1);
        system("clear");
        std::cout << "\n\n\n검색중:";
        std::cout << " /#############_______/" << std::endl;
        std::cout << "검색내용:"<< detail_company_name << std::endl;
        sleep(1);
        system("clear");
        std::cout << "\n\n\n검색중:";
        std::cout << " /####################/" << std::endl;
        std::cout << "검색내용:"<< detail_company_name << std::endl;
        sleep(1);
        system("clear");
        
        std::cout << "================================" << std::endl;
        rc = sqlite3_exec(db, detail_announcement.c_str(), callback, 0, &err_msg); //쿼리문 전달 및 실행
        std::cout << "================================" << std::endl;
        
        std::cout << "1. 기업정보" << std::endl;
        std::cout << "기업정보를 원하시면 1번 또는 ""기업정보""를 입력해주세요." << std::endl;
        std::string choice;
        std::cin >> choice;
        if(choice == "기업정보" || choice == "1")
        {
            system("clear");
            std::cout << "==========기업상세정보==========" << std::endl;
            std::string company_information = "SELECT 회사명, 설립년도, 사원수, 산업, 기업형태 FROM resume WHERE 회사명 LIKE '%"+ detail_company_name +"%';";
            int dd = sqlite3_exec(db, company_information.c_str(), callback, 0, &err_msg);
            std::cout << "================================" << std::endl;
        }
        else
        {
            std::cout << "잘못된 입력입니다. 메인페이지로 돌아갑니다." << std::endl;
            sleep(2);
            system("clear");
            break;
        }

        if(rc != SQLITE_OK)
        {
            std::cout << "error" << std::endl;
            exit(1);
        }
        std::cout << "메인페이지로 이동을 원하시면 아무키나 입력해주세요." << std::endl;
        std::cin >> main_page;

        sqlite3_finalize(res); //벡터 핸들정리
        sqlite3_close(db); //DB 닫기
        system("clear");
        break;
    }
}