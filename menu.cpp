#include "db.h"

void log::menu()
{
    start art;
    art.start_image();
    int choice = 0;
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
            if(log_count == 1)
            {
                std::cout << "로그인 상태입니다." << std::endl;
                sleep(1);
                system("clear");
                break;
            }
            log_in();
            break;
        }
        case 2:
        {
            if(log_count == 1)
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