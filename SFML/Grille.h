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

    void initialiserDepuisFichier(const std::string& chemin);
    void sauvegarderDansFichier(const std::string& chemin) const;
    void calculerProchaineIteration();
    void afficherEtat() const;
    bool estStable() const; // Nouvelle méthode
};

#endif // GRILLE_H
