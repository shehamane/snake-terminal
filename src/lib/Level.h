#ifndef SNAKE_TERMINAL_FRAME_H
#define SNAKE_TERMINAL_FRAME_H

#include <vector>
#include <string>

#include "Vector2D.h"

enum class Cell{Free, Obstacle, Food, Head};

typedef std::vector<std::string> Pattern;

class Level {
private:
    int width, height;
    Vector2D startPosition;
    std::vector<std::vector<Cell>> level;

    static Vector2D validateAndGetSize(Pattern pattern);
public:
    Level(){};
    Level(Pattern pattern);

    int getWidth();
    int getHeight();
    Vector2D getStartPosiion();
    Cell get(Vector2D position);

    void set(Vector2D position, Cell value);
    void set(std::vector<Vector2D> positions, Cell value);

    std::vector<Vector2D> getFreePositions();
};


#endif //SNAKE_TERMINAL_FRAME_H
