#include "game.h"
#include <limits>
#include <iostream>
#include <cstdlib>


using namespace std;

void Game::start() {
    cout << "Welcome to my battleship game!\n";
    cout << "\nLegend\n00 = ship,\nMM = miss,\nHH = hit,\n~~ = sea\n" << endl;
    cout << "Enter Y to start the game...";

    char charEnlarger;
    while (true) {
        cin >> charEnlarger;
        charEnlarger = toupper(charEnlarger);

        if (charEnlarger == 'Y') {
            break;
        }
        cout << "Invalid input. Enter Y to start the game: ";
        cin.clear();
        cin.ignore();
    }
    clearScreen();

    currentPlayer = 0;
    placeShips(); // Player 1 places all ships
    clearScreen();

    switchPlayer(); // Switch to player 2
    placeShips(); // Player 2 places all ships
    clearScreen();

    gameLoop(); // Start of the game
}

void Game::clearScreen() {
    system("CLS");
}

void Game::promptNextPlayer() const {
    char charEnlarger;
    cout << "Player " << currentPlayer + 1 << "'s turn, press Y to continue...";

    while (true) {
        cin >> charEnlarger;
            charEnlarger = toupper(charEnlarger);
        if (charEnlarger == 'Y') {
            break;
        }{
            cout << "Invalid input. Player " << currentPlayer + 1 << ", press Y to continue: ";
            cin.clear();
            cin.ignore();
        }
    }
    clearScreen();
}

void Game::switchPlayer() {
    currentPlayer = 1 - currentPlayer;
}

void Game::placeShips() {
    vector<int> shipSizes = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1}; // Sizes of ships to place
    promptNextPlayer();

    for (int size : shipSizes) {
        placeSingleShip(size);
        clearScreen();
    }
}

void Game::placeSingleShip(int size) {
    int col;
    char rowChar, orientation;

    while (true) {
        cout << "Player " << currentPlayer + 1 << ", place a " << size << " mast ship:" << endl;
        oceanGrids[currentPlayer].display();

        // Enter row'n col- he/he-michael jackson B)
        cout << "Enter coordinates and orientation H- Horizontal/V- vertical (eg. A1 H): ";
        cin >> rowChar >> col;
        rowChar = toupper(rowChar);
        if (cin.fail() || (rowChar < 'A' || rowChar > 'J')) {
            cout << "Invalid row, you need to choose letter between A-J, please try again" << endl;
            cin.clear();
            cin.ignore();
            continue;
        }
        if (cin.fail() || col < 1 || col > 10) {
            cout << "Invalid column. You need to pick from 1-10, please try again." << endl;
            cin.clear();
            cin.ignore();
            continue;
        }
        int row = rowChar - 'A';
        col -= 1;

        // Enter orientation
        // cout << "Enter orientation (H-horizontal, V-vertical): ";
        cin >> orientation;
        orientation = toupper(orientation);
        if (cin.fail() || (orientation != 'H' && orientation != 'V')) {
            cout << "Invalid orientation. You need to choose from H/V, please try again." << endl;
            cin.clear();
            cin.ignore();
            continue;
        }

        bool horizontal = (orientation == 'H');

        // Adjust ship position if it goes out of bounds
        if (horizontal && col + size > 10) {
            col = 10 - size;
        } else if (!horizontal && row + size > 10) {
            row = 10 - size;
        }

        //
        if (!canPlaceShip(row, col, size, horizontal)) {
            cout << "Ship overlaps another ship or directly borders one of it's sides, try different coordinates." << endl;
            continue;
        }

        // Place the ship
        oceanGrids[currentPlayer].placeShip(size, row, col, orientation);
        clearScreen();
        oceanGrids[currentPlayer].display();
        cout << "Press C to confirm or D to deny your choice: ";
        char confirm;
        cin >> confirm;
        confirm = toupper(confirm);
        if (confirm == 'C') break;  // Confirm choice

        // Remove improperly placed ship
        oceanGrids[currentPlayer].removeShip(size, row, col, orientation);
    }
}

void Game::displayLegend() {
    cout << "Legend\n00 = ship,\nMM = miss,\nHH = hit,\n~~ = sea\n" << endl;
}

void Game::gameLoop() {
    bool gameRunning = true;
    bool hit = false;
    bool lastShotHit = true;  // prevents miss from displaying at start because when it's first turn you can't miss or shoot

    // Start from player 1
    currentPlayer = -1;

    while (gameRunning) {
        if (!hit) {
            clearScreen();
            if (!lastShotHit && currentPlayer != -1) {  // displays miss when it's not first turn and last shot was a miss
                cout << "Miss!" << endl;
            }
            currentPlayer = (currentPlayer + 1) % 2;
        }
        promptNextPlayer();
        displayLegend();
        cout << "Player " << currentPlayer + 1 << "'s turn." << endl;
        vector<string> oceanLines = oceanGrids[currentPlayer].getLines();
        vector<string> targetLines = targetGrids[currentPlayer].getLines();

        for (size_t i = 0; i < oceanLines.size(); ++i) {
            cout << oceanLines[i] << "    " << targetLines[i] << endl;
        }

        cout << "Enter attack coordinates (eg. A1): ";  // Shoot coordinates input
        char rowChar;
        int col;

        while (true) {
            cin >> rowChar >> col;
            rowChar = toupper(rowChar);
            
            if (!cin.fail() && rowChar >= 'A' && rowChar  =< 'J'
                && col >= 1 && col <= 10) {
                break;
            }

            if (cin.fail() || (rowChar < 'A' || rowChar > 'J')) {
                cout << "Invalid row, you need to choose letter between A-J, please try again ";
                cin.clear();
                cin.ignore();
                continue;
            }
            if (cin.fail() || col < 1 || col > 10) {
                cout << "Invalid column. You need to pick from 1-10, please try again." << endl;
                cin.clear();
                cin.ignore();
            }
        }
        int row = rowChar - 'A';
        col -= 1;

        if (targetGrids[currentPlayer].isHit(row, col)) {
            cout << "You already hit this spot. Please try different coordinates." << endl;
            continue;
        }

        if (checkHit(row, col)) {
            targetGrids[currentPlayer].markHit(row, col);
            cout << "Hit!" << endl;
            hit = true;  // Shoot again if hit
            lastShotHit = true;

            int opponent = 1 - currentPlayer;
            if (oceanGrids[opponent].isShipSunk(row, col)) {
                int shipSize = getShipSize(row, col, opponent);
                cout << shipSize << " mast ship destroyed!" << endl;
            }
        } else {
            targetGrids[currentPlayer].markMiss(row, col);
            hit = false;  // Switch if miss
            lastShotHit = false;
        }

        if (checkAllShipsDestroyed(1 - currentPlayer)) {
            cout << "Player " << currentPlayer + 1 << " wins!" << endl;
            gameRunning = false;
        }
    }
}

bool Game::checkHit(int row, int col) {
    int opponent = 1 - currentPlayer;
    if (oceanGrids[opponent].checkHit(row, col)) {
        oceanGrids[opponent].grid[row][col] = "HH"; // Hit mark
        return true;
    }
    return false;
}

bool Game::checkAllShipsDestroyed(int player) {
    for (int row = 0; row < 10; ++row) {
        for (int col = 0; col < 10; ++col) {
            if (oceanGrids[player].isOccupied(row, col) &&
                !oceanGrids[player].isShipSunk(row, col)) { //very important to win condition
                return false;
                }
        }
    }

    return true;
}

bool Game::canPlaceShip(int row, int col, int length, bool horizontal) {
    for (int i = 0; i < length; ++i) {
        int r = row + (horizontal ? 0 : i);
        int c = col + (horizontal ? i : 0);

        if (r >= 10 || c >= 10 || r < 0 || c < 0) {
            return false;  //
        }

        if (oceanGrids[currentPlayer].isOccupied(r, c)) { //
            return false;
        }

        for (int dr = -1; dr <= 1; ++dr) {         // Checks borders without corners
            for (int dc = -1; dc <= 1; ++dc) {
                if (abs(dr) == 1 && abs(dc) == 1) continue;
                int nr = r + dr;
                int nc = c + dc;
                if (nr >= 0 && nr < 10 && nc >= 0 && nc < 10) {
                    if (oceanGrids[currentPlayer].isOccupied(nr, nc)) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

int Game::getShipSize(int row, int col, int player) {
    int size = 1;

    int r = row, c = col;

    //checks columns
    while (c > 0 && (oceanGrids[player].grid[r][c - 1] == "OO" || oceanGrids[player].grid[r][c - 1] == "HH")) {
        c--;
        size++;
    }
    c = col;
    while (c < 9 && (oceanGrids[player].grid[r][c + 1] == "OO" || oceanGrids[player].grid[r][c + 1] == "HH")) {
        c++;
        size++;
    }

    //checks rows if columns max is 1
    if (size == 1) {
        while (r > 0 && (oceanGrids[player].grid[r - 1][c] == "OO" || oceanGrids[player].grid[r - 1][c] == "HH")) {
            r--;
            size++;
        }
        r = row;
        while (r < 9 && (oceanGrids[player].grid[r + 1][c] == "OO" || oceanGrids[player].grid[r + 1][c] == "HH")) {
            r++;
            size++;
        }
    }

    return size;
}
