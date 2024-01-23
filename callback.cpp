#include "db.h"

int searching::callback(void *NotUsed,int argc,char **argv, char **azColName)
{    
    NotUsed = 0;
    
    for (int i = 0; i < argc; i++)
    {
        printf("%s:%s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    
    std::cout << "\n";
    
    return 0;
}