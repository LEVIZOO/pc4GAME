#include <iostream>  
#include <string>  

using namespace std;  

void drawGrid(int grid[6][7]);  
bool playTurn(int grid[6][7], int column, int player);  
string gagne(int grid[6][7], int player);  
string gagneVertical(int grid[6][7], int player);  
string gagneHorizontal(int grid[6][7], int player);  
string gagneDiagonalLeft(int grid[6][7], int player);  
string gagneDiagonalRight(int grid[6][7], int player);  
int IA(int grid[6][7], int player);  
int modejoeur();  

int main() {  
    int grille[6][7] = {0};  
    int player = 1;  
    int joeur = modejoeur();  

    while (true) {  
        drawGrid(grille);  

        if (joeur == 1 || (joeur == 2 && player == 1)) {  
            cout << "Joueur " << player << " -> col : ";  
            int choix;  
            cin >> choix;  

            if (choix == 0) {  
                break; 
            }    

            bool success = false;  

            if (choix >= 1 && choix <= 7) {  
                int col = choix - 1; 
                success = playTurn(grille, col, player);  
            }  

            system("CLS");  

            if (!success) {  
                cout << "Votre choix est incorrect\n";  
            } else {  
                string result = gagne(grille, player);  
                if (result != "Pas de gagnant") {  
                    cout << result << endl;  
                    break;  
                }  
                if (player == 1) {
                player = 2;
            } else {
                player = 1;
            }  
            }  
        } else if (joeur == 2 && player == 2) {  
            int col = IA(grille, player);  
            if (col != -1) {  
                playTurn(grille, col, player);  
                system("CLS");  
                cout << "Le PC a joué dans la colonne : " << (col + 1) << endl;   
                string result = gagne(grille, player);  
                if (result != "Pas de gagnant") {  
                    cout << result << endl;  
                    break;  
                }  
                player = 1; 
            }  
        }  
    }  

    return 0;  
}  

int modejoeur() {  
    int mode;  
    cout << "Choisir le mode de jeu :\n";  
    cout << "1. Joueur 1 contre Joueur 2\n";  
    cout << "2. Joueur 1 contre PC\n";  
    cout << "Entrez votre choix (1 ou 2) : ";  
    cin >> mode;  
    return mode;  
}  

int IA(int grid[6][7], int player) {  
    int robot = (player == 1) ? 2 : 1;  

    for (int col = 0; col < 7; col++) {  
        for (int line = 0; line < 6; line++) {  
            if (grid[line][col] == 0) {  
                grid[line][col] = player; 
                if (gagne(grid, player) != "Pas de gagnant") {  
                    grid[line][col] = 0;   
                    return col;  
                }  
                grid[line][col] = 0;  
                break;  
            }  
        }  
    }  

   
    for (int col = 0; col < 7; col++) {  
        for (int line = 0; line < 6; line++) {  
            if (grid[line][col] == 0) {  
                grid[line][col] = robot;  
                if (gagne(grid, robot) != "Pas de gagnant") {  
                    grid[line][col] = 0; 
                    return col; 
                }  
                grid[line][col] = 0;  
                break;  
            }  
        }  
    }  

      
    while (true) {  
        int col = rand() % 7; 
        for (int line = 5; line >= 0; line--) {  
            if (grid[line][col] == 0) {  
                return col;  
            }  
        }  
    }  
}  

string gagne(int grid[6][7], int player) {  
    if (gagneVertical(grid, player) != "Pas de gagnant" ||  
        gagneHorizontal(grid, player) != "Pas de gagnant" ||  
        gagneDiagonalLeft(grid, player) != "Pas de gagnant" ||  
        gagneDiagonalRight(grid, player) != "Pas de gagnant") {  
        return "Le joueur " + to_string(player) + " a gagné!";  
    }  
    return "Pas de gagnant";  
}  

string gagneVertical(int grid[6][7], int player) {  
    for (int col = 0; col < 7; col++) {  
        int count = 0;  
        for (int line = 0; line < 6; line++) {  
            if (grid[line][col] == player) {  
                count++;  
                if (count == 4) {  
                    return "Gagné par le joueur " + to_string(player);  
                }  
            } else {  
                count = 0; 
            }  
        }  
    }  
    return "Pas de gagnant";  
}  

string gagneHorizontal(int grid[6][7], int player) {  
    for (int line = 0; line < 6; line++) {  
        int count = 0;  
        for (int col = 0; col < 7; col++) {  
            if (grid[line][col] == player) {  
                count++;  
                if (count == 4) {  
                    return "Gagné par le joueur " + to_string(player);  
                }  
            } else {  
                count = 0;  
            }  
        }  
    }  
    return "Pas de gagnant";  
}  

string gagneDiagonalLeft(int grid[6][7], int player) {  
    for (int col = 0; col < 4; col++) {  
        for (int line = 0; line < 6; line++) {  
            if (grid[line][col] == player) {  
                if (line <= 2 &&  
                    grid[line][col] == player &&  
                    grid[line + 1][col + 1] == player &&  
                    grid[line + 2][col + 2] == player &&  
                    grid[line + 3][col + 3] == player) {  
                    return "Gagné par le joueur " + to_string(player);  
                }  
            }  
        }  
    }  
    return "Pas de gagnant";  
}  

string gagneDiagonalRight(int grid[6][7], int player) {  
    for (int col = 3; col < 7; col++) {  
        for (int line = 0; line < 6; line++) {  
            if (grid[line][col] == player) {  
                if (line <= 2 &&  
                    grid[line][col] == player &&  
                    grid[line + 1][col - 1] == player &&  
                    grid[line + 2][col - 2] == player &&  
                    grid[line + 3][col - 3] == player) {  
                    return "Gagné par le joueur " + to_string(player);  
                }  
            }  
        }  
    }  
    return "Pas de gagnant";  
}  

void drawGrid(int grid[6][7]) {  
    for (int ligne = 0; ligne < 6; ligne++) {  
        cout << "|";  
        for (int col = 0; col < 7; col++) {  
            if (grid[ligne][col] == 1) {  
                cout << "\033[31m*\033[37m";   
            } else if (grid[ligne][col] == 2) {  
                cout << "\033[32m*\033[37m";   
            } else {  
                cout << "\033[37m*\033[37m";   
            }  
            cout << "|";  
        }  
        cout << "\n";  
    }  
}  

bool playTurn(int grid[6][7], int column, int player) {  
    for (int line = 5; line >= 0; line--) {  
        if (grid[line][column] == 0) {   
            grid[line][column] = player;  
            return true;  
        }  
    }  
    return false;  
}