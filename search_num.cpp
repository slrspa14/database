#include "db.h"

std::string searching::search_numbers() //검색건수 및 공고출력 //이게되네 string 반환형 함수도 가능하다
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

std::string searching::search_numbers1() //검색건수 및 공고출력
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


std::string searching::search_numbers2() //검색건수 및 공고출력
{
    sqlite3 *db; //핸들, 파일디스크립터같은
    char *err_msg = 0; // 오류메시지
    sqlite3_stmt* res;
    int rc = sqlite3_open("/home/aiot11/Downloads/worknet", &db); //열고
    std::string detail_search_num;
    std::string  sql= "SELECT COUNT(*) FROM resume WHERE 근무지역 LIKE '%"+ region +"%' AND 경력 LIKE '%"+ career +"%' AND 학력 LIKE '%"+ education +"%';";

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

std::string searching::search_numbers3() //검색건수 및 공고출력
{
    sqlite3 *db; //핸들, 파일디스크립터같은
    char *err_msg = 0; // 오류메시지
    sqlite3_stmt* res;
    int rc = sqlite3_open("/home/aiot11/Downloads/worknet", &db); //열고
    std::string detail_search_num;
    std::string  sql= "SELECT COUNT(*) FROM resume WHERE 회사명 LIKE '%"+ ser1 +"%';";

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