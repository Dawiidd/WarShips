#include "oceanGrid.h"
#include <iostream>

using namespace std;

OceanGrid::OceanGrid() {
    initializeGrid();
}

void OceanGrid::initializeGrid() {
    grid = vector(10, vector<string>(10, "~~"));
}

void OceanGrid::display() const {
    for (const auto& line : getLines()) {
        cout << line << endl;
    }
}

vector<string> OceanGrid::getLines() const {
    vector<std::string> lines;
    lines.push_back("|---==== Player's board ====---|");
    lines.push_back("_ 01 02 03 04 05 06 07 08 09 10");
    char rowLabel = 'A';
    for (const auto& row : grid) {
        std::string line;
        line += rowLabel++;
        line += " ";
        for (const auto& cell : row) {
            line += cell + " ";
        }
        lines.push_back(line);
    }
    return lines;
}

void OceanGrid::placeShip(int size, int row, int col, char orientation) {
    if (orientation == 'H') {
        for (int i = 0; i < size; ++i) {
            grid[row][col + i] = "OO";
        }
    } else if (orientation == 'V') {
        for (int i = 0; i < size; ++i) {
            grid[row + i][col] = "OO";
        }
    }
}

void OceanGrid::removeShip(int size, int row, int col, char orientation) {
    if (orientation == 'H') {
        for (int i = 0; i < size; ++i) {
            grid[row][col + i] = "~~";
        }
    } else if (orientation == 'V') {
        for (int i = 0; i < size; ++i) {
            grid[row + i][col] = "~~";
        }
    }
}

bool OceanGrid::checkHit(int row, int col) {
    return grid[row][col] == "OO";
}

bool OceanGrid::isOccupied(int row, int col) {
    return grid[row][col] != "~~";
}

bool OceanGrid::isShipSunk(int row, int col) const {
    if (grid[row][col] != "OO" && grid[row][col] != "HH") {
        return false;
    }

    for (int i = col; i >= 0 && (grid[row][i] == "OO" || grid[row][i] == "HH"); i--) {     // Check horizontally
        if (grid[row][i] == "OO") {
            return false;
        }
    }
    for (int i = col; i < 10 && (grid[row][i] == "OO" || grid[row][i] == "HH"); i++) {
        if (grid[row][i] == "OO") {
            return false;
        }
    }

    for (int i = row; i >= 0 && (grid[i][col] == "OO" || grid[i][col] == "HH"); i--) {     // Check vertically
        if (grid[i][col] == "OO") {
            return false;
        }
    }
    for (int i = row; i < 10 && (grid[i][col] == "OO" || grid[i][col] == "HH"); i++) {
        if (grid[i][col] == "OO") {
            return false;
        }
    }

    return true;
}