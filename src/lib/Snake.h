#ifndef SNAKE_TERMINAL_SNAKE_H
#define SNAKE_TERMINAL_SNAKE_H

#include <vector>

#include "Level.h"
#include "Vector2D.h"

class Snake {
private:
    int length;
    Vector2D direction;
    Vector2D head;
    std::vector<Vector2D> bodyPositions;
    Level *level;
    bool isGrowing;

public:
    Snake(Level *lvl);

    void move();

    void growUp();

    std::vector<Vector2D> getBodyPositions();

    Vector2D getHead();

    Vector2D getDirection();

    void setDirection(Vector2D directionNew);
};


#endif //SNAKE_TERMINAL_SNAKE_H
