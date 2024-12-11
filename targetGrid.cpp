#include "targetGrid.h"
#include <iostream>

using namespace std;

TargetGrid::TargetGrid() {
    initializeGrid();
}

void TargetGrid::initializeGrid() {
    grid = vector(10, vector<string>(10, "~~"));
}

void TargetGrid::display() const {
    for (const auto& line : getLines()) {
        cout << line << endl;
    }
}

vector<string> TargetGrid::getLines() const {
    vector<string> lines;
    lines.push_back("|---==== Target's board ====---|");
    lines.push_back(" _ 01 02 03 04 05 06 07 08 09 10");
    char rowLabel = 'A';
    for (const auto& row : grid) {
        string line;
        line += rowLabel++;
        line += " ";
        for (const auto& cell : row) {
            line += cell + " ";
        }
        lines.push_back(line);
    }
    return lines;
}

void TargetGrid::markHit(int row, int col) {
    grid[row][col] = "HH";
}

void TargetGrid::markMiss(int row, int col) {
    grid[row][col] = "MM";
}