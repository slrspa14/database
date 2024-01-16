#include <iostream>
#include "SQLiteCpp.h"

int main()
{
    SQLiteCpp db;

    if (db._sqlite3_open(DIR))
        std::cout << "1. DB 연결" << std::endl;
    else
        return 0;

    
    std::cout << "2. DB 쿼리 실행" << std::endl;
    std::vector res = db.GetAllRecords();
    for (size_t i = 0; i < res.size(); i++)
    {
        for (size_t j = 0; j < res[0].size(); j++)
        {
            std::cout << res[i][j];
        }

        std::cout << std::endl;
    }

    if (db._sqlite3_close())
        std::cout << "3. DB 연결 해제" << std::endl;

    return 0;
}