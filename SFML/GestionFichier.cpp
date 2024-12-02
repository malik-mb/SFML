#include "GestionFichier.h"
#include <stdexcept>
#include <fstream>

void GestionFichier::chargerConfiguration(Grille& grille, const std::string& chemin) {
    grille.initialiserDepuisFichier(chemin);
}

void GestionFichier::sauvegarderConfiguration(const Grille& grille, const std::string& chemin) {
    grille.sauvegarderDansFichier(chemin);
}