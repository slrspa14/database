#include <sqlite3.h>
#include <stdio.h>
#include <string>
#include <iostream>


int main(void)
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
    std::string join_id, join_pw, join_email, join_pnum;
    std::cout << "ID:";
    std::cin >> join_id;
    std::cout << "PW";
    std::cin >> join_pw;
    std::cout << "email:";
    std::cin >> join_email;
    std::cout << "HP:";
    std::cin >> join_pnum;

    std::string sql = "INSERT INTO 'join' VALUES('asdf', 2222, 'Volkswagen', 21600);" //db에 보낼 값
                    "INSERT INTO 'join' VALUES('"+join_id+"', '"+join_pw+"', '"+join_email+"', '"+join_pnum+"');";

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