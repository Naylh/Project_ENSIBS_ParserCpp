#include "Position.h"

Position::Position(int x, int y) {
    this->_x = x;
    this->_y = y;
}

int Position::getX() const {
    return this->_x;
}

int Position::getY() const {
    return this->_y;
}

bool Position::operator==(Position otherPosition) const {
    return this->_x == otherPosition.getX() && this->_y == otherPosition.getY();
}