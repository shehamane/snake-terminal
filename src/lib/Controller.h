#ifndef SNAKE_TERMINAL_CONTROLLER_H
#define SNAKE_TERMINAL_CONTROLLER_H

#include <termios.h>
#include "Snake.h"

class Controller {
private:
    struct termios oldIO, currentIO;
    int tty, l;
    char buf[2];
    float FPS;

    Level level;
    Snake snake;

    void initTermios();
    void resetTermios();

    char getKey();
    void sleep(unsigned int delay = 0) const;
    void printFrame();
public:
    Controller(Pattern lvl, float fps);
    ~Controller();

    void generateFood();
    bool checkCollision();
    bool checkFood();
    void start();
    bool handleKey(char key);
};


#endif //SNAKE_TERMINAL_CONTROLLER_H
