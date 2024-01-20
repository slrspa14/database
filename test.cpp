#include <sqlite3.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstdlib>
#include <ctime>

void start_page();
void start_image();
int insert(std::string id, std::string pw, std::string email, std::string pnum);
int join_page();
int callback(void *, int, char **, char **);
int view(void);

int main()
{
    // start_image();
    // start_page();
    join_page();

    return 0;
}

int join_page() // 회원가입 페이지
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
            join = " SELECT ID FROM 'join' WHERE ID = '" + join_id +"'; "; // 입력한 join_id랑 쿼리문 비교
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
            join = "SELECT EMAIL FROM 'join' WHERE EMAIL = '"+ join_email + "';";
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
            join = "SELECT PNUM FROM 'join' WHERE PNUM = '"+ join_pnum + "';";

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
    
    join = "INSERT INTO 'join' VALUES('"+join_id+"','"+join_pw+"','"+join_email+"','"+join_pnum+"');"; //쿼리문 보내고
    rc = sqlite3_prepare_v2(db, join.c_str(), -1, &res, 0);// 준비
    rc = sqlite3_step(res); // 실행

    sqlite3_finalize(res); //SQL 쿼리 핸들 정리
    sqlite3_close(db); //DB 닫기
    std::cout << "회원가입이 완료되었습니다." << std::endl;
    std::cout << "회원가입내역" << std::endl;
    std::cout << join_id << std::endl;
    std::cout << join_pw << std::endl;
    std::cout << join_email << std::endl;
    std::cout << join_pnum << std::endl;
    return 0;
}

void log_in()
{
    system("clear");
    sqlite3 *db; //핸들, 파일디스크립터같은
    char *err_msg = 0; // 오류메시지
    sqlite3_stmt* res;

    std::cout << "로그인페이지" << std::endl;
    std::string log_id, log_pw, join;
    int rc = sqlite3_open("/home/aiot11/Downloads/worknet", &db); //열고

    std::cout << "ID:";
    std::cin >> log_id;
    std::cout << "PW:";
    std::cin >> log_pw;
    while(1)
    {
        join = " SELECT ID FROM 'join' WHERE ID = '" + log_id +"' AND '"+ log_pw +"';"; // 입력한 join_id랑 쿼리문 비교
        rc = sqlite3_prepare_v2(db, join.c_str(), -1, &res, 0); // 준비
        rc = sqlite3_step(res); // 실행하기
        if(rc == SQLITE_ROW) // db랑 사용자 입력이 같다면 중복검사
        {
            std::cout << "로그인 성공" << std::endl;
            std::cout << "공고페이지로 이동하기" << std::endl;
        }
        else
        {
            std::cout << "일치하는 ID 및 PW가 없습니다." << std::endl;
            std::cout << "다시 입력해주세요." << std::endl;
            std::cout << "ID:";
            std::cin >> log_id;
            std::cout << "PW";
            std::cin >> log_pw;
        }
    }

}
int insert(std::string id, std::string pw, std::string email, std::string pnum)
{
    sqlite3 *db;
    char *err_msg = 0;
    
    int rc = sqlite3_open("/home/aiot11/Downloads/worknet", &db);
    
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return 1;
    }

    std::string sql = "INSERT INTO 'join' VALUES('"+id+"', '"+pw+"', '"+email+"', '"+pnum+"');";

    rc = sqlite3_exec(db, sql.c_str(), 0, 0, &err_msg);
    
    if (rc != SQLITE_OK )
    {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        
        return 1;
    }
    sqlite3_close(db);
    
    return 0;
}


int view(void)
{
    sqlite3 *db;
    char *err_msg = 0;
    
    int rc = sqlite3_open("/home/aiot11/Downloads/worknet", &db);
    
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Cannot open database: %s\n", 
                sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return 1;
    }
    
    const char *sql = "select * from resume";
        
    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
    
    if (rc != SQLITE_OK )
    {
        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);
        
        return 1;
    } 
    
    sqlite3_close(db);
    
    return 0;
}

int callback(
    void *NotUsed,
    int argc,
    char **argv, 
    char **azColName)
{    
    NotUsed = 0;
    
    for (int i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    
    printf("\n");
    
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

void start_page()
{
    std::cout << "번호를 선택해주세요." << std::endl;
    std::cout << "1. 로그인" << std::endl;
    std::cout << "2. 회원가입" << std::endl;
    int choice = 0;
    std::cin >> choice;
    if(choice == 1)
    {
        std::cout << "로그인 페이지로 이동" << std::endl;
        // log_in();
    }
    else if(choice == 2)
    {
        std::cout << "회원가입 페이지로 이동" << std::endl;
        join_page();
    }
    else
    {
        std::cout << "잘못된 선택입니다. 다시 선택해주세요" << std::endl;   
    }
}

