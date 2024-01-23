// #include <iostream>
// #include <fstream>
// #include <unistd.h>
// using namespace std;
// int main(void)
// {
//     cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡄⠀⠀⠀⠀⠀⠀⠀⠀" << endl;
//     cout << "⠀⠀⠀⢀⡀⠀⠀⠀⠀⢸⡇⠀⠀⠀⠀⠀⠀⠀⠀" << endl;
//     cout << "⠀⠀⠀⠈⠻⣦⡀⠀⠀⢸⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀" << endl;
//     cout << "⠀⠀⠀⠀⠀⠈⠻⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << endl;
//     cout << "⠀⣀⣀⣀⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << endl;
//     cout << "⠀⠉⠉⠉⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << endl;
//     sleep(1);
// }


#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>
 
static struct termios initial_settings, new_settings;
 
static int peek_character = -1;
 
void init_keyboard()
{
    tcgetattr(0,&initial_settings);
    new_settings = initial_settings;
    new_settings.c_lflag &= ~ICANON;
    new_settings.c_lflag &= ~ECHO;
    new_settings.c_cc[VMIN] = 1;
    new_settings.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &new_settings);
}
 
void close_keyboard()
{
    tcsetattr(0, TCSANOW, &initial_settings);
}
 
int _kbhit()
{
    unsigned char ch;
    int nread;
 
    if (peek_character != -1) return 1;
    new_settings.c_cc[VMIN]=0;
    tcsetattr(0, TCSANOW, &new_settings);
    nread = read(0,&ch,1);
    new_settings.c_cc[VMIN]=1;
    tcsetattr(0, TCSANOW, &new_settings);
    if(nread == 1)
    {
        peek_character = ch;
        return 1;
    }
    return 0;
}
 
int _getch()
{
    char ch;
 
    if(peek_character != -1)
    {
        ch = peek_character;
        peek_character = -1;
        return ch;
    }
    read(0,&ch,1);
    return ch;
}
 
int _putch(int c) 
{
    // putchar(c);
    fflush(stdout);
    return c;
}
 
// use above functions in this way
int main()
{
    init_keyboard();
    //왼 75 오 77 위 72 아래 80
    while (1) 
    {
        if (_kbhit()) {
            int ch = _getch();
            _putch(ch);
            switch (ch) 
            {
                case 75:
                    std::cout << "왼쪽" << std::endl;
                    break;
                case 77:
                    std::cout << "오른쪽" << std::endl;
                    break;
                case 72:
                    std::cout << "위" << std::endl;
                    break;
                case 80:
                    std::cout << "아래" << std::endl;
                    break;

            }
        }
    }
    close_keyboard();
 
    return 0;
}