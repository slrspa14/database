#ifndef TEST_H
#define TEST_H
#include <sqlite3.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstdlib>
#include <ctime>


using namespace std;

class db
{
    private:
    std::string log_id;
    std::string log_pw;
    std::string join_id;
    std::string join_pw;
    std::string join_email;
    std::string join_pnum;
    int log_count = 0;
    public:

    
};
#endif