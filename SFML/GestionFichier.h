#ifndef GESTIONFICHIER_H
#define GESTIONFICHIER_H

#include "Grille.h"
#include <string>

class GestionFichier {
public:
    static void sauvegarderConfiguration(const Grille& grille, const std::string& chemin);
    static void chargerConfiguration(Grille& grille, const std::string& chemin);
    static void sauvegarderIteration(const Grille& grille, const std::string& dossier, int iteration);
};

// Fonction utilitaire pour créer un dossier
void creerDossier(const std::string& dossier);

#endif // GESTIONFICHIER_H
