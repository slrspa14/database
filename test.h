#ifndef TEST_H
#define TEST_H
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <unistd.h>
#include <vector>
#include <sstream>
#include <sqlite3.h>
#include <stdio.h>


using namespace std;

// class test_work
// {
//     private:

//     public:
    
// };
void start_image();
void start_page();
// void log_in();
int join();
void join_insert(std::string id, std::string pw, std::string email, std::string pnum);
// int DataBaseOutput(std::string user);
#endif