#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream> 

using namespace std; 

void drawGrid(int grid[7][6]);
bool playTurn(int grid[7][6], int column, int player);
string checkWin(int grid[7][6], int player);
string checkVertical(int grid[7][6], int player);
string checkHorizontal(int grid[7][6], int player);
string checkDiagonalLeft(int grid[7][6], int player);
string checkDiagonalRight(int grid[7][6], int player);

string intToString(int num) {
    ostringstream oss;
    oss << num;
    return oss.str();
}

int main(int argc, char** argv) {
    int grille[7][6] = {};
    string choix;
    int player = 1;

    drawGrid(grille);

    while (true) {
        cout << "player_" << player << " -> col :";
        cin >> choix;

        if (choix == "exit") {
            break;
        }

        bool success = false;

        if (choix.size() == 1) {
            if (choix[0] >= '0' && choix[0] <= '7') {
                int col = choix[0] - '0';

                success = playTurn(grille, col, player);
            }
        }

        system("CLS");

        if (!success) {
            cout << "votre choix est incorrect\n";
        } else {
            
            string result = checkWin(grille, player);
            if (result != "AUCUN GAGNANT") {
                cout << result ;
                break; 
            }

            
            if (player == 1) {
                player = 2;
            } else {
                player = 1;
            }
        }

        drawGrid(grille);
    }

    return 0;
}

string checkWin(int grid[7][6], int player) {
    if (checkVertical(grid, player) == "le joeur qui es a gagne est le joeur" + (player) ||
        checkHorizontal(grid, player) == "le joeur qui es a gagne est le joeur " + (player) ||
        checkDiagonalLeft(grid, player) == "le joeur qui es a gagne est le joeur" + (player)  ||
        checkDiagonalRight(grid, player) == "le joeur qui es a gagne est le joeur" + (player) ) {
        return "le joeur qui es a gagne est le joeur" + (player);
    }
    return "personne na gagne";
}


string checkVertical(int grid[7][6], int player) {
    for (int col = 0; col < 7; col++) {
        int count = 0;
        for (int line = 0; line < 6; line++) {
            if (grid[col][line] == player) {
                count++;
                if (count == 4) {
                    return "GAGN� " + intToString(player);
                }
            } else {
                count = 0; // R�initialiser le compteur
            }
        }
    }
    return "AUCUN GAGNANT";
}

// V�rification horizontale
string checkHorizontal(int grid[7][6], int player) {
    for (int line = 0; line < 6; line++) {
        int count = 0;
        for (int col = 0; col < 7; col++) {
            if (grid[col][line] == player) {
                count++;
                if (count == 4) {
                    return "GAGN� " + intToString(player);
                }
            } else {
                count = 0; // R�initialiser le compteur
            }
        }
    }
    return "AUCUN GAGNANT";
}

// V�rification diagonale gauche
string checkDiagonalLeft(int grid[7][6], int player) {
    for (int col = 0; col < 7; col++) {
        for (int line = 0; line < 6; line++) {
            if (grid[col][line] == player) {
                // V�rifier la diagonale gauche
                if (col <= 3 && line <= 2 && 
                    grid[col][line] == player &&
                    grid[col + 1][line + 1] == player &&
                    grid[col + 2][line + 2] == player &&
                    grid[col + 3][line + 3] == player) {
                    return "GAGN� " + intToString(player);
                }
            }
        }
    }
    return "AUCUN GAGNANT";
}

// V�rification diagonale droite
string checkDiagonalRight(int grid[7][6], int player) {
    for (int col = 0; col < 7; col++) {
        for (int line = 0; line < 6; line++) {
            if (grid[col][line] == player) {
                // V�rifier la diagonale droite
                if (col >= 3 && line <= 2 && 
                    grid[col][line] == player &&
                    grid[col - 1][line + 1] == player &&
                    grid[col - 2][line + 2] == player &&
                    grid[col - 3][line + 3] == player) {
                    return "GAGN� " + intToString(player);
                }
            }
        }
    }
    return "AUCUN GAGNANT";
}


void drawGrid(int grille[7][6]) {
    for (int ligne = 0; ligne < 6; ligne++) {
        cout << "|";
        for (int col = 0; col < 7; col++) {
            if (grille[col][ligne] == 1) {
                cout << "\033[31m*\033[37m"; 
            } else if (grille[col][ligne] == 2) {
                cout << "\033[32m*\033[37m"; 
            } else {
                cout << "\033[37m*\033[37m"; 
            }
            cout << "|";
        }
        cout << "\n";
    }
}


bool playTurn(int grid[7][6], int column, int player) {
    for (int line = 5; line >= 0; line--) {
        if (grid[column - 1][line] == 0) {
            grid[column - 1][line] = player;
            return true;
        }
    }
    return false;
}
