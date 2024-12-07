#ifndef GRILLE_H
#define GRILLE_H

#include "Cellule.h"
#include <vector>
#include <string>

class Grille {
private:
    int nbLignes;
    int nbColonnes;
    std::vector<std::vector<Cellule>> cellules;
    std::vector<std::vector<bool>> etatPrecedent; // Ajout pour stocker l'état précédent
public:
    Grille(int lignes, int colonnes);

    int getNbLignes() const;
    int getNbColonnes() const;

    Cellule& getCellule(int x, int y);
    const Cellule& getCellule(int x, int y) const;
    bool estStable() const; // Nouvelle méthode
    void initialiserDepuisFichier(const std::string& chemin);
    void sauvegarderDansFichier(const std::string& chemin) const;
    void calculerProchaineIteration();
    void afficherEtat() const;
    void miseAJour() {
        // Sauvegarder l'état précédent pour la détection de stabilité
        etatPrecedent.clear();
        etatPrecedent.resize(nbLignes, std::vector<bool>(nbColonnes));
        for (int i = 0; i < nbLignes; ++i) {
            for (int j = 0; j < nbColonnes; ++j) {
                etatPrecedent[i][j] = cellules[i][j].estVivante();
            }
        }

        calculerProchaineIteration();
    }
};

#endif // GRILLE_H
