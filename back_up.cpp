#include <sqlite3.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstdlib>
#include <ctime>

void announcement(); //랜덤공고
void start_image();//시작 아스키아트
void join_page(); // 회원가입
void search(); // 검색
int callback(void *, int, char **, char **);
void log_in(); // 로그인
void menu(); // 메인 스위치
void detail_search(); // 상세검색
std::string search_numbers(); // 키워드검색 검색건수 출력
std::string search_numbers1(); // 상세검색 검색건수 출력
std::string search_numbers2(); //검색건수 및 공고출력
// constexpr unsigned int HashCode(const char* str);


std::string region;
std::string career;
std::string education; //detail search, search_numbers1
std::string search3; // detail search
std::string user_search; //search
int log_count = 0; //log_in

int main()
{
    menu();
    return 0;
}

// constexpr unsigned int HashCode(const char* str)
// {
//     return str[0] ? static_cast<unsigned int>(str[0]) + 0xEDB8832Full * HashCode(str + 1) : 8603;
// }

void menu()
{
    start_image();
    // std::string choice;
    int choice = 0;
    while(choice < 4)
    {
        announcement();
        std::cout << "============================" << std::endl;
        std::cout << "1. 로그인" << std::endl;
        std::cout << "2. 회원가입" << std::endl;
        std::cout << "3. 검색" << std::endl;
        std::cout << "4. 종료" << std::endl;
        std::cout << "============================" << std::endl;
        std::cout << "선택:";
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            if(log_count==1)
            {
                std::cout << "로그인 상태입니다." << std::endl;
                sleep(1);
                system("clear");
                break;
            }
            log_in();
            break;
        case 2:
            if(log_count == 1)
            {
                std::cout << "로그인 상태입니다." << std::endl;
                sleep(1);
                system("clear");
                break;
            }
            join_page();
            break;
        case 3:
            search();
            break;
        case 4:
            break;
        }
    }
}

void join_page() // 회원가입 페이지
{
    system("clear");
    sqlite3 *db; //핸들, 파일디스크립터같은
    char *err_msg = 0; // 오류메시지
    sqlite3_stmt* res;

    std::string join;
    std::string join_id, join_pw, join_email, join_pnum;
    
    std::cout << "회원가입" << std::endl;
    int rc = sqlite3_open("/home/aiot11/Downloads/worknet", &db); //db 열기

    //아이디
    while(1)
    {

        std::cout << "ID:";
        std::cin >> join_id;
        while(1)
        {
            join = " SELECT ID FROM USER_DATA WHERE ID = '" + join_id +"'; "; // 입력한 join_id랑 쿼리문 비교
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

void log_in()
{
    system("clear");
    sqlite3 *db; //핸들, 파일디스크립터같은
    char *err_msg = 0; // 오류메시지
    sqlite3_stmt* res;

    std::cout << "로그인페이지" << std::endl;
    std::string log_id, log_pw, join;
    int pw;
    int rc = sqlite3_open("/home/aiot11/Downloads/worknet", &db); //열고

    std::cout << "ID:";
    std::cin >> log_id;
    std::cout << "PW:";
    // std::cin >> log_pw;
    std::cin >> pw;
    log_pw = std::to_string(pw); // str 형변환

    while(1)
    {   
        join = "SELECT USER_ID, PW FROM USER_DATA WHERE USER_ID = '"+ log_id +"' AND PW = '"+ log_pw + "';"; //ID,PW 검사 쿼리문
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
            break;
        }
        else
        {
            system("clear");
            std::cout << "일치하는 ID 및 PW가 없습니다." << std::endl;
            std::cout << "다시 입력해주세요." << std::endl;
            std::cout << "ID:";
            std::cin >> log_id;
            std::cin.ignore();
            std::cout << "PW:";
            std::cin >> pw;
            std::cin.ignore();
            log_pw = std::to_string(pw); // str 형변환
        }
    }
}

int callback(void *NotUsed,int argc,char **argv, char **azColName)
{    
    NotUsed = 0;
    
    for (int i = 0; i < argc; i++)
    {
        printf("%s:%s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    
    std::cout << "\n";
    
    return 0;
}

void start_image()
{
    std::string line;
    std::ifstream file("logo.txt");
    while(getline(file,line))
    {
        std::cout << line << std::endl;
    }
    sleep(2);
    system("clear");
}

void search()
{
    system("clear");
    int choice = 0;
    while(choice <= 3)
    {
        std::cout << "============================" << std::endl;
        std::cout << "          1. 검색" << std::endl;
        std::cout << "        2. 상세검색" << std::endl;
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
            std::string detail_search = "SELECT * FROM details WHERE 회사명 LIKE  '%"+ ser1 +"%';";

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
        break;
    }
}

void detail_search()//상세검색
{
    system("clear");
    while(1)
    {
        sqlite3 *db; //핸들, 파일디스크립터같은
        char *err_msg = 0; // 오류메시지

        int rc = sqlite3_open("/home/aiot11/Downloads/worknet", &db); //db 열기
        
        // std::string region, career, education;
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
        
        std::string  search3 = "SELECT * FROM resume WHERE 근무지역 LIKE '%"+ region +"%' AND 경력 LIKE '%"+ career +"%' AND 학력 LIKE '%"+ education +"%';";
        std::cout << "============================================" << std::endl;
        rc = sqlite3_exec(db, search3.c_str(), callback, 0, &err_msg); //쿼리문 전달 및 실행
        std::cout << "============================================" << std::endl;

        if(search_numbers1() == "0")
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

        //상세검색 들어가서 회사공고 들어가기
        std::string detail_company_name;
        std::cout << "공고상세정보 보기를 원하시면 회사명을 입력해주세요" << std::endl;
        std::cin >> detail_company_name;
        while(detail_company_name.size() < 9) //한글은 크기 3
        {
            std::cout << "검색어 입력시 3글자 이상으로 입력해주세요" << std::endl;
            std::cout << "검색:";
            std::cin >> detail_company_name;
        }
        std::string detail_announcement = "SELECT * FROM details WHERE 회사명 LIKE '%"+ detail_company_name + "%';"; //상세보기 쿼리문
        system("clear");
        rc = sqlite3_exec(db, detail_announcement.c_str(), callback, 0, &err_msg); //쿼리문 전달 및 실행

        std::cout << "기업정보" << std::endl;
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
        std::string wait;
        std::cout << "메인페이지로 이동을 원하시면 아무키나 입력해주세요." << std::endl;
        std::cin >> wait;
        sleep(1);
        sqlite3_close(db); //DB 닫기
        system("clear");
        break;
    }
}

void announcement()
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

std::string search_numbers() //검색건수 및 공고출력 //이게되네 string 반환형 함수도 가능하다
{
    sqlite3 *db; //핸들, 파일디스크립터같은
    char *err_msg = 0; // 오류메시지
    sqlite3_stmt* res;
    int rc = sqlite3_open("/home/aiot11/Downloads/worknet", &db); //열고
    std::string search_num;
    std::string sql = "SELECT COUNT(*) FROM resume WHERE 필요스킬 LIKE '%"+ user_search + "%';";

    rc=sqlite3_prepare_v2(db,sql.c_str(),-1,&res,nullptr);

    while((rc=sqlite3_step(res))==SQLITE_ROW)
    {
        search_num = reinterpret_cast<const char*>(sqlite3_column_text(res,0));
        std::cout<< "검색건수: "<< search_num << std::endl << std::endl;
    }
    sqlite3_finalize(res); //SQL 쿼리 핸들 정리
    sqlite3_close(db); //DB 닫기
    return search_num;
}

std::string search_numbers1() //검색건수 및 공고출력
{
    sqlite3 *db; //핸들, 파일디스크립터같은
    char *err_msg = 0; // 오류메시지
    sqlite3_stmt* res;
    int rc = sqlite3_open("/home/aiot11/Downloads/worknet", &db); //열고
    std::string detail_search_num;
    std::string  sql= "SELECT COUNT(*) FROM resume WHERE 근무지역 LIKE '%"+ region +"%' AND 경력 LIKE '%"+ career +"%' AND 학력 LIKE '%"+ education +"%';";

    rc = sqlite3_prepare_v2(db,sql.c_str(),-1,&res,nullptr);

    while((rc=sqlite3_step(res))==SQLITE_ROW)
    {
        detail_search_num = reinterpret_cast<const char*>(sqlite3_column_text(res,0));
        std::cout<< "검색건수: "<< detail_search_num << std::endl << std::endl;
    }

    sqlite3_finalize(res); //SQL 쿼리 핸들 정리
    sqlite3_close(db); //DB 닫기
    return detail_search_num;
}
std::string search_numbers2() //검색건수 및 공고출력
{
    sqlite3 *db; //핸들, 파일디스크립터같은
    char *err_msg = 0; // 오류메시지
    sqlite3_stmt* res;
    int rc = sqlite3_open("/home/aiot11/Downloads/worknet", &db); //열고
    std::string detail_search_num;
    std::string  sql= "SELECT * FROM resume WHERE 근무지역 LIKE '%"+ region +"%' AND 경력 LIKE '%"+ career +"%' AND 학력 LIKE '%"+ education +"%';";

    rc = sqlite3_prepare_v2(db,sql.c_str(),-1,&res,nullptr);

    while((sqlite3_step(res))==SQLITE_ROW)
    {
        detail_search_num = reinterpret_cast<const char*>(sqlite3_column_text(res,0));
        std::cout<< "검색건수: "<< detail_search_num << std::endl << std::endl;
    }

    sqlite3_finalize(res); //SQL 쿼리 핸들 정리
    sqlite3_close(db); //DB 닫기
    return detail_search_num;
}