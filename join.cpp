#include "test.h"

int join()
{
    sqlite3 *db;
    char *err_msg = 0;
    std::string join_id, join_pw, join_email, join_pnum; //저장할 변수
    //회원가입
    std::cout << "회원가입" << std::endl;
    std::cout << "ID:";
    std::cin >> join_id;
    std::cout << "PW(4자리 숫자만):";
    std::cin >> join_pw;

    while(join_pw.size() > 4 || join_pw.size() <= 3) // 4자리 아닐때
    {
        system("clear");
        std::cout << "비밀번호는 4자리만 가능합니다.\n다시 입력해주세요." << std::endl;
        std::cout << "PW(숫자 4자리):";
        std::cin >> join_pw;
    }

    std::cout << "e-mail:";
    std::cin >> join_email;
    std::cout << "H.P(-제외,11자리)";
    std::cin >> join_pnum;

    int rc = sqlite3_open("work.db", &db);

    if ( rc != SQLITE_OK)
    {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char * user = "SELECT ID FROM join WHERE ID =(" + "'" + join_id + "'" + ");";
                // "SELECT e-mail FROM join WHERE e-mail = join_email;"
                // "SELECT PNUM FROM join WHERE PNUM = join_pnum;";


    while(join_id == "SELECT ID FROM join WHERE ID")
    {
        std::cout << "중복된 ID입니다. 다시 입력해주세요";
        std::cin >> join_id;
    }
    while(join_email == "SELECT e-mail FROM join WHERE e-amil")
    {
        std::cout << "중복된 email입니다. 다시 입력해주세요" << std::endl;
        std::cout << "e-mail:";
        std::cin >> join_email;
    }
    while(join_pnum == "SELECT PNUM FROM join WHERE PNUM")
    {
        std::cout << "중복된 핸드폰번호입니다. 다시 입력해주세요" << std::endl;
        std::cout << "H.P(-제외,11자리)";
        std::cin >> join_pw;
    }

    rc = sqlite3_exec(db, user, 0, 0, &err_msg);

    //insert(); 성공하면 insert로 db에 저장하기
    // join_insert(join_id, join_pw, join_email, join_pnum);

    std::cout << "회원가입 성공" << std::endl;
    std::cout << "ID:" << join_id << std::endl;
    std::cout << "PW:" << join_pw << std::endl;
    std::cout << "e-mail:" << join_email << std::endl;
    std::cout << "핸드폰번호:" << join_pnum << std::endl;

    if(rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }
    sqlite3_close(db);
    return 0;
}