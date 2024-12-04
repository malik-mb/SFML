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

    int lignes, colonnes;
    fichier >> lignes >> colonnes;

    if (fichier.fail() || lignes <= 0 || colonnes <= 0) {
        throw std::runtime_error("Dimensions invalides dans le fichier.");
    }

    if (lignes != nbLignes || colonnes != nbColonnes) {
        throw std::runtime_error("Dimensions du fichier (" +
            std::to_string(lignes) + "x" + std::to_string(colonnes) +
            ") ne correspondent pas à la grille attendue (" +
            std::to_string(nbLignes) + "x" + std::to_string(nbColonnes) + ").");
    }

    for (int i = 0; i < nbLignes; ++i) {
        for (int j = 0; j < nbColonnes; ++j) {
            int etat;
            fichier >> etat;

            if (fichier.fail() || (etat != 0 && etat != 1)) {
                throw std::runtime_error("Valeur invalide dans la grille à la position (" +
                    std::to_string(i) + ", " + std::to_string(j) + ").");
            }

            cellules[i][j] = Cellule(etat == 1);
        }
    }
}

void Grille::sauvegarderDansFichier(const std::string& chemin) const {
    std::ofstream fichier(chemin);
    if (!fichier) {
        throw std::runtime_error("Impossible d'ouvrir le fichier pour sauvegarder : " + chemin);
    }

    fichier << nbLignes << " " << nbColonnes << "\n"; // Écrit la taille de la grille en première ligne

    for (int i = 0; i < nbLignes; ++i) {
        for (int j = 0; j < nbColonnes; ++j) {
            fichier << (getCellule(i, j).estVivante() ? 1 : 0) << " ";
        }
        fichier << "\n"; // Ajoute un retour à la ligne après chaque rangée
    }
}


void Grille::calculerProchaineIteration() {
    for (int i = 0; i < nbLignes; ++i) {
        for (int j = 0; j < nbColonnes; ++j) {
            int vivantes = 0;
            for (int di = -1; di <= 1; ++di) {
                for (int dj = -1; dj <= 1; ++dj) {
                    if (di == 0 && dj == 0) continue;

                    // Indices voisins avec gestion torique
                    int ni = (i + di + nbLignes) % nbLignes;
                    int nj = (j + dj + nbColonnes) % nbColonnes;

                    if (cellules[ni][nj].estVivante()) {
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
bool Grille::estStable() const {
    for (int i = 0; i < nbLignes; ++i) {
        for (int j = 0; j < nbColonnes; ++j) {
            // Comparer l'état actuel avec l'état précédent
            if (cellules[i][j].estVivante() != etatPrecedent[i][j]) {
                return false; // Si un état diffère, ce n'est pas stable
            }
        }
    }
    return true; // Tous les états sont identiques
}
void Grille::afficherEtat() const {
    for (const auto& ligne : cellules) {
        for (const auto& cellule : ligne) {
            std::cout << (cellule.estVivante() ? "1" : "0");
        }
        std::cout << "\n";
    }
}
