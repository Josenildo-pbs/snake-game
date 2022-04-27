#ifndef SNAKE_H // include guard
#define SNAKE_H
// #ifdef __cplusplus
// extern "C"
// {
// #endif
#include <iostream>
using namespace std;

typedef struct
{
    int x;
    int y;
} position_t;

class Snake
{
private:
    int velocity[2] = {1, 0};
    position_t *body;
    unsigned int length = 1;
    int steps = 5;

public:
    Snake(int x, int y);
    void printer();
    void run();
    void eat();
    void setVelocity(int x, int y);
    int getSteps();
    void setSteps(int steps);
    unsigned int getLength();
    position_t *getBody();
};
// #ifdef __cplusplus
// }
// #endif
#endif