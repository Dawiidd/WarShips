#ifndef TARGETGRID_H
#define TARGETGRID_H

#include <vector>
#include <string>

using namespace std;

class TargetGrid {
public:
    TargetGrid();
    void display() const;
    vector<std::string> getLines() const;
    void markHit(int row, int col);
    void markMiss(int row, int col);
    bool isHit(int row, int col) const {
        return grid[row][col] == "HH" || grid[row][col] == "HH";
    }


private:
    vector<vector<string>> grid;
    void initializeGrid();
};

#endif