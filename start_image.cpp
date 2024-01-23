#include "db.h"

// void test_work::start_image()
void start::start_image()
{
    std::string line;
    std::ifstream file("saram.txt");
    while(getline(file,line))
    {
        std::cout << line << std::endl;
    }
    sleep(2);
    system("clear");
    file.close();
}