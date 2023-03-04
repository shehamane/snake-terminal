#ifndef SNAKE_TERMINAL_VECTOR2D_H
#define SNAKE_TERMINAL_VECTOR2D_H


class Vector2D {
private:
    int x, y;

public:
    Vector2D();

    Vector2D(int x, int y);

    int getX();

    void setX(int xNew);

    int getY();

    void setY(int yNew);

    Vector2D operator+(Vector2D const &vec);

    friend bool operator==(Vector2D const &lhs, Vector2D const &rhs) {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    };
};

#endif //SNAKE_TERMINAL_VECTOR2D_H
