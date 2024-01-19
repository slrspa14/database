#include "test.h"

int join()
{
    sqlite3 *db;
    char *err_msg = 0;
    sqlite3_stmt *res;
    std::string user;
    std::string join_id, join_pw, join_email, join_pnum;

    std::cout << "회원가입" << std::endl;
    std::cout << "ID:";
    std::cin >> join_id;
    std::cout << "PW(4자리 숫자만):";
    std::cin >> join_pw;

    while(join_pw.size() > 4 || join_pw.size() <= 3)
    {
        system("clear");
        std::cout << "비밀번호는 4자리만 가능합니다.\n다시 입력해주세요." << std::endl;
        std::cout << "PW(숫자 4자리):";
        std::cin >> join_pw;
    }

    std::cout << "e-mail:";
    std::cin >> join_email;
    std::cout << "H.P(-제외,11자리):";
    std::cin >> join_pnum;

    int rc = sqlite3_open("worknet", &db);

    if ( rc != SQLITE_OK)
    {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    // user = "SELECT ID FROM join WHERE ID ='" +join_id+ "';";
    user = " SELECT ID FROM join WHERE ID = '" + join_id +"'; ";

    rc = sqlite3_prepare_v2(db, user.c_str(), -1, &res, 0);
    // rc = sqlite3_prepare_v2(db, user.c_str(), -1, &res, 0);
    rc = sqlite3_step(res);
    if (rc == SQLITE_OK)
    {
        sqlite3_bind_int(res, 1, 2);
    }
    else
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    while(1)
    {
        int step = sqlite3_step(res);
        if (step == SQLITE_ROW)
        {
            std::cout << sqlite3_column_text(res,0) << std::endl;
        }
        else
            break;
    }
    sqlite3_finalize(res);
    sqlite3_close(db);
    return 0;
}