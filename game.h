#ifndef GAME_H
#define GAME_H

#include <vector>
#include "oceanGrid.h"
#include "targetGrid.h"
#include "ships.h"

using namespace std;

class Game {
public:
    void start();
    static void clearScreen();
    void switchPlayer();
    void placeShips();
    void gameLoop();
    void promptNextPlayer() const;
    void promptNextPlayerIfMiss();
    static void displayLegend();

private:
    int currentPlayer;
    OceanGrid oceanGrids[2];
    TargetGrid targetGrids[2];
    vector<Ship> playerShips[2];
    void placeSingleShip(int size);
    bool checkHit(int row, int col);
    void markShipHit(int row, int col);
    bool checkAllShipsDestroyed(int player);
    bool canPlaceShip(int row, int col, int length, bool horizontal);
    char toUpperCase(char toUpperCase);
    int getShipSize(int row, int col, int player);
};

#endif