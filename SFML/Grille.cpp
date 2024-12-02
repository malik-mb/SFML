#include "Grille.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

Grille::Grille(int lignes, int colonnes)
    : nbLignes(lignes), nbColonnes(colonnes), cellules(lignes, std::vector<Cellule>(colonnes)) {
}

int Grille::getNbLignes() const {
    return nbLignes;
}

int Grille::getNbColonnes() const {
    return nbColonnes;
}

Cellule& Grille::getCellule(int x, int y) {
    return cellules[x][y];
}

const Cellule& Grille::getCellule(int x, int y) const {
    return cellules[x][y];
}

void Grille::initialiserDepuisFichier(const std::string& chemin) {
    std::ifstream fichier(chemin);
    if (!fichier) {
        throw std::runtime_error("Impossible d'ouvrir le fichier : " + chemin);
    }

    for (int i = 0; i < nbLignes; ++i) {
        for (int j = 0; j < nbColonnes; ++j) {
            int etat;
            fichier >> etat;
            cellules[i][j] = Cellule(etat == 1);
        }
    }
}

void Grille::sauvegarderDansFichier(const std::string& chemin) const {
    std::ofstream fichier(chemin);
    if (!fichier) {
        throw std::runtime_error("Impossible d'ouvrir le fichier pour sauvegarder : " + chemin);
    }

    for (int i = 0; i < nbLignes; ++i) {
        for (int j = 0; j < nbColonnes; ++j) {
            fichier << (getCellule(i, j).estVivante() ? 1 : 0) << " ";
        }
        fichier << "\n";
    }
}

void Grille::calculerProchaineIteration() {
    for (int i = 0; i < nbLignes; ++i) {
        for (int j = 0; j < nbColonnes; ++j) {
            int vivantes = 0;
            for (int di = -1; di <= 1; ++di) {
                for (int dj = -1; dj <= 1; ++dj) {
                    if (di == 0 && dj == 0) continue;
                    int ni = i + di, nj = j + dj;
                    if (ni >= 0 && ni < nbLignes && nj >= 0 && nj < nbColonnes && cellules[ni][nj].estVivante()) {
                        ++vivantes;
                    }
                }
            }
            if (cellules[i][j].estVivante()) {
                cellules[i][j].definirEtatSuivant(vivantes == 2 || vivantes == 3);
            }
            else {
                cellules[i][j].definirEtatSuivant(vivantes == 3);
            }
        }
    }

    for (auto& ligne : cellules) {
        for (auto& cellule : ligne) {
            cellule.actualiserEtat();
        }
    }
}

void Grille::afficherEtat() const {
    for (const auto& ligne : cellules) {
        for (const auto& cellule : ligne) {
            std::cout << (cellule.estVivante() ? "1" : "0");
        }
        std::cout << "\n";
    }
}