#include "test.h"

// void test_work::start_image()
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