#ifndef SHIPS_H
#define SHIPS_H

#include <vector>

using namespace std;

class Ship {
public:
    Ship(int size);
    int getSize() const;

private:
    int size;
};

#endif