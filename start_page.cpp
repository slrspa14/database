#include "test.h"
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
        log_in();
    }
    else if(choice == 2)
    {
        std::cout << "회원가입 페이지로 이동" << std::endl;
        join();
    }
    else
    {
        std::cout << "잘못된 선택입니다. 다시 선택해주세요" << std::endl;
        // std::cin >> choice;
    }
}