#include <iostream>            //directive au preprocesseur, qui inclut la bibliothèque qui permet de gérer les entrées/sorties
#include <stdlib.h>           //inclut la bibliothèque qui gere l'exécution des commandes 
#include <string>            //inclut la bibliothèque qui gere les chaines de caractères
#include <ctime>            //inclut la bibliothèque qui  gère le temps, les dates et specialement ds ce code génère les nombres aléatoires

void drawGrid(int grid[7][6]);                                    //fonction qui cree un tableau 6x7 et affiche son contenue
bool playTurn(int grid[7][6], int column, int player);           //fonction qui place un jeton dans une colonne choisi
int aiMove(int grid[7][6]);                                     //fonction utiliser par l'ia pour choisir une colonne
bool checkWin(int grid[7][6], int player);                     //fonction de verification du gagnant

int main(){                                                  //fonction principale

    int grille[7][6] = {};                                 //initialise une grille 7X6 vide
    std::string choix;                                    //instruction qui recupère le choix de la colonne du joueur
    int player = 1;                                      //initialise le joueur 1 à l'humain

    drawGrid(grille);                                  //affiche la grille initialement vide

    while (true){                                                         //boucle
        bool success = false;                                            //variables pour verifier si un couip à ete jouer
        
        if (player == 1) {                                             //tour du joueur humain(1)
            std::cout << "player_" << player << " -> col :";          //affiche le message qui demande au joueur de choisir une colonne 
            std::cin >> choix;                                       //recupère la valeur entrer

            if (choix == "exit"){                                  //quitter le jeu si l'utilisateur entre "exit"
                break;
            }

            if (choix.size() == 1 && choix[0] >= '1' && choix[0] <= '7'){                           //Vérifie que  le choix n'est qu'un seul caractère compris entre 1 et 7
                int col = choix[0] - '0';                                                          //Convertit le caractère en entier
                success = playTurn(grille, col, player);                                          //appel la fonction playturn et joue dans la colonne choisie 
            }

            if (!success){                                                                            
                std::cout << "Entrez un numero de colonne non pleine, compris entre 1 et 7\n";  //affiche le message en cas d'erreur sur la donné entré
                continue;
            }
        } else {                                                                              //tour de l'IA
            int col = aiMove(grille);                                                        //dans le cas ou il y a pas d'erreur sur la donné, la fonction aiMove génère un nombre aléatoire pour le tour de l'IA
            playTurn(grille, col + 1, player);                                              //place le jeton de l'IA dans la colonne choisi 
            std::cout << "IA a joué dans la colonne " << col << "\n";                      //affiche la colone choisit par l'ia
        }

        system("CLS");                                                                  //Efface l'écran sur windows

        drawGrid(grille);                                                             //affiche la mise à jour apres chaque

        
        if (checkWin(grille, player)) {                                             //Vérifie si le joueur actuel a gagné
            std::cout << "Joueur " << player << ", vous avez gagnez la partie!\n"; //affiche le message si le joueur à gagner la partie et le jeu se termine
            break;
        }

        
        if (player == 1) player = 2;                                           //Change de joueur pour le tour suivant 
        else player = 1;
    }

    return 0;
}

void drawGrid(int grille[7][6]){                                             //affiche la grille du jeu
    for (int ligne = 0; ligne < 6; ligne++){                                //parcours les lignes de la grille
        std::cout << "|";                                                  //affiche ce séparateur entre tte les colonne
        for (int col = 0; col < 7; col++){                                  
            if (grille[col][ligne] == 1){                                //si la cellule contient le jeton du joueur 1, la marque de couleur rouge
                std::cout << "\033[31m*\033[37m";
            } else if (grille[col][ligne] == 2){                       //si la cellule contient le jeton du joueur 2, la marque de couleur verte
                std::cout << "\033[32m*\033[37m";
            } else {                                                 //affiche la cellule vide
                std::cout << "\033[37m*\033[37m";
            }
            std::cout << "|";
        }
        std::cout << "\n";                                       //passe à la ligne suivante
    }
}

bool playTurn(int grid[7][6], int column, int player){        //joue ds une colone donné
    for (int line = 5 ; line >= 0; line--){                  //permet de parcourir par le bas de la colonne
        if (grid[column - 1][line] == 0){                   //verifie si la case est vide
            grid[column - 1][line] = player;               //place le jeton ds la 1er case libre
            return true;                                  //Retourne vrai si la case est vide
        }
    }
    return false;                                      //Retourne faux si la colonne est pleine
}

int aiMove(int grid[7][6]){
    srand(time(0));                                 //Initialise la génération aléatoire avec l'heure actuelle
    int col;                                       //declare la colone choisit
    bool validMove = false;                      

    while (!validMove){                          // boucle qui repète jusqu'a trouver une colonne valide
        col = rand() % 7;                       //Choisit une colonne aléatoire entre 0 et 6
        for (int line = 6; line >= 1; line--) {
            if (grid[col][line] == 1) {       // Vérifie que la colonne n'est pas pleine
                validMove = true;
                break;
            }
        }
    }
    return col;
}

bool checkWin(int grid[7][6], int player) {                       //fonction qui verifie si un joueur à aligné 4 jetons 

    //Verifie les lignes horizontales
    for (int ligne = 0; ligne < 6; ligne++) {
        for (int col = 0; col < 4; col++) {                     
            if (grid[col][ligne] == player && grid[col+1][ligne] == player &&
                grid[col+2][ligne] == player && grid[col+3][ligne] == player) {
                return true;
            }
        }
    }

    //Verifie les colonnes verticales
    for (int col = 0; col < 7; col++) {
        for (int ligne = 0; ligne < 3; ligne++) {
            if (grid[col][ligne] == player && grid[col][ligne+1] == player &&
                grid[col][ligne+2] == player && grid[col][ligne+3] == player) {
                return true;
            }
        }
    }

    //Verifie les diagonales montantes
    for (int col = 0; col < 4; col++) {
        for (int ligne = 3; ligne < 6; ligne++) {
            if (grid[col][ligne] == player && grid[col+1][ligne-1] == player &&
                grid[col+2][ligne-2] == player && grid[col+3][ligne-3] == player) {
                return true;
            }
        }
    }

    //Verifie les diagonales descendantes
    for (int col = 0; col < 4; col++) {
        for (int ligne = 0; ligne < 3; ligne++) {
            if (grid[col][ligne] == player && grid[col+1][ligne+1] == player &&
                grid[col+2][ligne+2] == player && grid[col+3][ligne+3] == player) {
                return true;
            }
        }
    }

    return false;                                              //retoure false si aucun alignement n'a été trouver
}