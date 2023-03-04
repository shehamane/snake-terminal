#include "Level.h"

Vector2D Level::validateAndGetSize(Pattern pattern) {
    int height, width;
    if (pattern.size() < 5) {
        throw "Pattern size must be more than 5";
    }

    height = pattern.size();
    width = pattern[0].length();

    if (width < 5) {
        throw "Pattern size must be more than 5";
    }
    for (int i = 1; i < pattern.size(); ++i) {
        if (pattern[i].length() != width) {
            throw "Incorrect pattern size";
        }
    }

    bool startFounded = false;
    for (int y = 0; y < pattern.size(); ++y) {
        for (int x = 0; x < pattern[y].length(); ++x) {
            char c = pattern[y][x];
            if (!(c == ' ' || c == '#' || c == '*')) {
                throw "Incorrect cell " + c;
            }
            if (c == '*') {
                if (startFounded) {
                    throw "More than one starting cell found";
                } else {
                    startFounded = true;
                }
            }
        }
    }

    if (!startFounded) {
        throw "Starting cell not found";
    }

    return Vector2D(width, height);
}

Level::Level(Pattern pattern) {
    Vector2D size = validateAndGetSize(pattern);
    width = size.getX(), height = size.getY();
    level = std::vector<std::vector<Cell>>(height, std::vector<Cell>(width));

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            switch (pattern[y][x]) {
                case '#':
                    level[y][x] = Cell::Obstacle;
                    break;
                case ' ':
                    level[y][x] = Cell::Free;
                    break;
                case '*':
                    level[y][x] = Cell::Head;
                    startPosition = Vector2D(x, y);
            }
        }
    }
}

int Level::getWidth() {
    return width;
}

int Level::getHeight() {
    return height;
}

Vector2D Level::getStartPosiion() {
    return startPosition;
}

Cell Level::get(Vector2D position) {
    return level[position.getY()][position.getX()];
}

void Level::set(Vector2D position, Cell value) {
    level[position.getY()][position.getX()] = value;
}

void Level::set(std::vector<Vector2D> positions, Cell value) {
    for (Vector2D pos: positions) {
        set(pos, value);
    }
}

std::vector<Vector2D> Level::getFreePositions() {
    std::vector<Vector2D> freePositions;
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            if (level[y][x] == Cell::Free) {
                freePositions.push_back(Vector2D(x, y));
            }
        }
    }
    return freePositions;
}
