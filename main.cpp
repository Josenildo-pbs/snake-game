
// #include <unistd.h>
#include <thread>
#include <chrono>
#include <mutex>
#include <stdlib.h>
#include <iostream>
#include "snake.h"
// #include <cstdlib>
#ifdef __linux__
#include <termios.h>
char getch()
{
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return (buf);
}

#else
#include <conio.h>
#endif
void clear_screen()
{
#ifdef __linux__
    std::system("clear");
#else
    // Assume POSIX
    std::system("cls");

#endif
}
using namespace std;
Snake snake(0, 0);
char command = 's';

void printTable(int *size, position_t apple, position_t *obj, int objLen)
{
    int x = size[0] - 1;
    int y = size[1] - 1;
    bool status = false;
    for (int i = x; i >= 0; i--)
    {
        for (int j = 0; j <= y; j++)
        {
            status = true;

            for (int x = 0; x < objLen; x++)
            {
                if (j == obj[x].x && i == obj[x].y)
                {
                    std::cout << "(" << j << "," << i << ")";
                    status = false;
                    break;
                }
            }
            if (j == apple.x && i == apple.y && status == true)
            {
                std::cout << "("
                          << "*,*"
                          << ")";
                status = false;
            }
            if (status == true)
            {
                std::cout << "(   )";
            }
        }
        std::cout << std::endl;
    }
}

void keyboardInputTask()
{
    /* get terminal attributes */
    for (;;)
    {
        command = getch();

#ifdef __linux__
        switch (command)
        {
        case 'A':
            snake.setVelocity(0, 1);
            break;
        case 'B':
            snake.setVelocity(0, -1);
            break;
        case 'C':
            snake.setVelocity(1, 0);
            break;
        case 'D':
            snake.setVelocity(-1, 0);
            break;
        default:
            break;
        }
#else
        switch (command)
        {
        case 'H':
            snake.setVelocity(0, 1);
            break;
        case 'P':
            snake.setVelocity(0, -1);
            break;
        case 'M':
            snake.setVelocity(1, 0);
            break;
        case 'K':
            snake.setVelocity(-1, 0);
            break;
        default:
            break;
        }

#endif
    }
}
void judge(position_t *apple, position_t *body, int bodySize, int *tableSize)
{

    if (apple->x == body[0].x && apple->y == body[0].y)
    {
        snake.eat();
        apple->x = rand() % tableSize[0];
        apple->y = rand() % tableSize[1];
    }
    else if ((tableSize[0] - 1) == body[0].x && (tableSize[1] - 1) == body[0].y)
    {
        // TODO GAME OVER
    }
    else
    {
        snake.run();
    }
}

void renderTask(void)
{
    int size[2] = {10, 10};
    position_t apple = {.x = (rand() % size[0]), .y = (rand() % size[1])};

    for (;;)
    {

        printTable(size, apple, snake.getBody(), snake.getLength());
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        judge(&apple, snake.getBody(), snake.getLength(), size);
        clear_screen();
    }
}
int main()
{
    thread kbTask(keyboardInputTask);
    thread renTask(renderTask);
    kbTask.join();
    renTask.join();
    return 0;
}
