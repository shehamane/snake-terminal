#include <termios.h>
#include <fcntl.h>
#include <unistd.h>

#include "Controller.h"
#include "Level.h"

#define ESC "\033"
#define home()            printf(ESC "[H") //Move cursor to the indicated row, column (origin at 1,1)
#define clrscr()        printf(ESC "[2J") //lear the screen, move to (1,1)
#define gotoxy(x, y)        printf(ESC "[%d;%dH", y, x);
#define visible_cursor() printf(ESC "[?251");
#define resetcolor() printf(ESC "[0m")
#define set_display_atrib(color)    printf(ESC "[%dm",color)


Controller::Controller(Pattern lvl, float fps) : level(lvl), snake(&level) {
    FPS = fps;
    clrscr();
    initTermios();
}

Controller::~Controller() {
    resetTermios();
}

void Controller::initTermios() {
    tty = open("/dev/tty", O_RDWR);
    tcgetattr(tty, &oldIO);
    currentIO = oldIO;
    currentIO.c_lflag &= ~ICANON;
    currentIO.c_lflag &= ~ECHO;
    currentIO.c_cc[VMIN] = 0;
    currentIO.c_cc[VTIME] = 0;

//    system("xset r rate 100 10");
    tcsetattr(tty, TCSANOW, &currentIO);
}

void Controller::resetTermios() {
    tcsetattr(0, TCSANOW, &oldIO);
//    system("xset r rate 600 25");
}

char Controller::getKey() {
    l = read(tty, buf, 1);
    return buf[0];
}

void Controller::sleep(unsigned int delay) const {
    double milliseconds;
    clock_t time_end;
    milliseconds = 1000 / FPS;
    time_end = clock() + (delay + milliseconds) * CLOCKS_PER_SEC / 1000;
    while (clock() < time_end) {
    }
}

void Controller::printFrame() {
    home();
    clrscr();
    for (int y = 0; y < level.getHeight(); ++y) {
        for (int x = 0; x < level.getWidth(); ++x) {
            switch (level.get(Vector2D(x, y))) {
                case Cell::Obstacle:
                    printf("#");
                    break;
                case Cell::Food:
                    printf("o");
                    break;
                case Cell::Head:
                    printf("X");
                    break;
                case Cell::Free:
                    printf(" ");
                    break;
            }
        }
        printf("\n");
    }
    this->sleep();
}

void Controller::generateFood() {
    auto freePositions = level.getFreePositions();
    int randInt = (rand() % static_cast<int> (freePositions.size()));
    Vector2D newFoodPosition = freePositions[randInt];
    level.set(newFoodPosition, Cell::Food);
}

bool Controller::checkCollision() {
    return level.get(snake.getHead() + snake.getDirection()) == Cell::Obstacle;
}

bool Controller::checkFood() {
    return level.get(snake.getHead() + snake.getDirection()) == Cell::Food;
}

void Controller::start() {
    generateFood();

    while (true) {
        printFrame();
        if (handleKey(getKey())) {
            break;
        }
        if (checkCollision()) {
            break;
        }
        if (checkFood()) {
            snake.growUp();
            generateFood();
        }
        snake.move();
    }
}

bool Controller::handleKey(char key) {
    switch (key) {
        case 'w':
            if (!(snake.getDirection() == Vector2D(0, 1)))
                snake.setDirection(Vector2D(0, -1));
            break;
        case 'a':
            if (!(snake.getDirection() == Vector2D(1, 0)))
                snake.setDirection(Vector2D(-1, 0));
            break;
        case 's':
            if (!(snake.getDirection() == Vector2D(0, -1)))
                snake.setDirection(Vector2D(0, 1));
            break;
        case 'd':
            if (!(snake.getDirection() == Vector2D(-1, 0)))
                snake.setDirection(Vector2D(1, 0));
            break;
        case 'q':
            return true;
            break;
    }
    return false;
}
