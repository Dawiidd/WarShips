#include "ships.h"

Ship::Ship(int size) : size(size) {}

int Ship::getSize() const {
    return size;
}