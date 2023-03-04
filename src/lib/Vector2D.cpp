#include "Vector2D.h"

Vector2D::Vector2D() : x(0), y(0) {}

Vector2D::Vector2D(int x, int y) : x(x), y(y) {}

int Vector2D::getX() {
    return x;
}

void Vector2D::setX(int xNew) {
    x = xNew;
}

int Vector2D::getY() {
    return y;
}

void Vector2D::setY(int yNew) {
    y = yNew;
}

Vector2D Vector2D::operator+(const Vector2D &vec) {
    return Vector2D(this->x + vec.x, this->y + vec.y);
}
