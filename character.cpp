#include "Character.h"

Character::Character(int startX, int startY) 
    : x(startX), y(startY) {}

void Character::move(int dx, int dy) {
    x += dx;
    y += dy;
}

int Character::getX() const {
    return x;
}

int Character::getY() const {
    return y;
}

void Character::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}
