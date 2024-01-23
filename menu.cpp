#include "db.h"

void start::menu()
{
    start_image();
    int choice = 0;
    log log_cnt;
    while(choice < 4)
    {
        searching an;
        an.announcement();
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
        {
            if(log_cnt.log_count == 1)
            {
                std::cout << "로그인 상태입니다." << std::endl;
                sleep(1);
                system("clear");
                break;
            }
            log login;
            login.log_in();
            break;
        }
        case 2:
        {
            if(log_cnt.log_count == 1)
            {
                std::cout << "로그인 상태입니다." << std::endl;
                sleep(1);
                system("clear");
                break;
            }
            join join;
            join.join_page();
            break;
        }
        case 3:{
            searching ser;
            ser.search();
            break;
        }
        case 4:
            break;
        }
    }
}