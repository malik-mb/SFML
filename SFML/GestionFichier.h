#ifndef GESTIONFICHIER_H
#define GESTIONFICHIER_H

#include "Grille.h"

class GestionFichier {
public:
    static void chargerConfiguration(Grille& grille, const std::string& chemin);
    static void sauvegarderConfiguration(const Grille& grille, const std::string& chemin);
};

#endif // GESTIONFICHIER_H
