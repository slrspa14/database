#ifndef DB_H
#define DB_H
#include <sqlite3.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstdlib>
#include <ctime>


// using namespace std;

class start
{
    public:
    void start_image();
    void menu();
};
class join
{
    private:
    std::string join_id;
    std::string join_pw;
    std::string join_email;
    std::string join_pnum;

    public:
    void join_page();

};
class log
{
    private:
    std::string log_id;
    std::string log_pw;

    public:
    void log_in();
    int log_count = 0;
};
class searching
{
    private:
    std::string region;
    std::string career;
    std::string education;
    std::string search3;
    std::string user_search;
    std::string main_page;
    
    public:
    void announcement();
    void search();
    void detail_search();
    std::string search_numbers();
    std::string search_numbers1();
    std::string search_numbers2();
    static int callback(void *, int, char **, char **);
};
#endif