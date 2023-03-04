#include "Snake.h"

Snake::Snake(Level *lvl) : level(lvl), head(lvl->getStartPosiion()), length(1) {
    isGrowing = false;
    direction = Vector2D(1, 0);
    bodyPositions = std::vector<Vector2D>();
    bodyPositions.push_back(head);
}

void Snake::move() {
    head = head + direction;

    if (head.getX() < 0) {
        head.setX(level->getWidth() - 1);
    } else if (head.getX() == level->getWidth()) {
        head.setX(0);
    }

    if (head.getY() < 0) {
        head.setY(level->getHeight() - 1);
    } else if (head.getY() == level->getHeight()) {
        head.setY(0);
    }

    Vector2D tailPos = bodyPositions[length - 1];
    bodyPositions.insert(bodyPositions.begin(), head);

    if (!isGrowing) {
        bodyPositions.pop_back();
        level->set(tailPos, Cell::Free);
    }else{
        isGrowing = false;
    }
    level->set(head, Cell::Head);
    for (int i = 1; i < length; ++i) {
        level->set(bodyPositions[i], Cell::Obstacle);
    }
}

void Snake::growUp() {
    ++length;
    isGrowing = true;
}

std::vector<Vector2D> Snake::getBodyPositions() {
    return bodyPositions;
}

Vector2D Snake::getHead() {
    return head;
}

Vector2D Snake::getDirection() {
    return direction;
}

void Snake::setDirection(Vector2D directionNew) {
    direction = directionNew;
}
