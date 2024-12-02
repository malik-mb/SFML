#include <iostream>
#include "Grille.h"
#include "ModeConsole.h"
#include "ModeGraphique.h"
#include "SFMLInterface.h"
#include "GestionFichier.h"

int main() {
    int nbLignes = 20, nbColonnes = 20;
    Grille grille(nbLignes, nbColonnes);

    // Demander le chemin du fichier
    std::string cheminFichier;
    std::cout << "Veuillez entrer le chemin du fichier de configuration : ";
    std::cin >> cheminFichier;

    // Charger la configuration depuis le fichier
    try {
        GestionFichier::chargerConfiguration(grille, cheminFichier);
    }
    catch (const std::exception& e) {
        std::cerr << "Erreur de chargement du fichier : " << e.what() << "\n";
    }

    // Choisir le mode
    std::cout << "Choisissez le mode :\n1 - Mode Console\n2 - Mode Graphique\n";
    int modeChoisi;
    std::cin >> modeChoisi;

    if (modeChoisi == 1) {
        ModeConsole modeConsole(grille);
        modeConsole.lancerSimulation();
    }
    else if (modeChoisi == 2) {
        auto sfml = std::make_unique<SFMLInterface>(nbColonnes * 10, nbLignes * 10);
        ModeGraphique modeGraphique(grille, std::move(sfml));
        modeGraphique.lancerSimulation();
    }
    else {
        std::cerr << "Mode invalide.\n";
    }

    // Sauvegarder la configuration dans le fichier
    try {
        GestionFichier::sauvegarderConfiguration(grille, cheminFichier);
    }
    catch (const std::exception& e) {
        std::cerr << "Erreur de sauvegarde du fichier : " << e.what() << "\n";
    }

    return 0;
}
