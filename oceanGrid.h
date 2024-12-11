#ifndef OCEANGRID_H
#define OCEANGRID_H

#include <vector>
#include <string>

using namespace std;
class OceanGrid {
public:
    OceanGrid();
    void display() const;
    vector<string> getLines() const;
    void placeShip(int size, int row, int col, char orientation);
    void removeShip(int size, int row, int col, char orientation);
    bool checkHit(int row, int col);
    bool isOccupied(int row, int col);
    bool isShipSunk(int row, int col) const;
    vector<vector<string>> grid;

private:
    void initializeGrid();
};

#endif // OCEANGRID_H