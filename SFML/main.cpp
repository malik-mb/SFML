#include <iostream>
#include <memory>
#include "Grille.h"
#include "ModeConsole.h"
#include "ModeGraphique.h"
#include "SFMLInterface.h"
#include "GestionFichier.h"

int main() {
    int nbLignes = 49, nbColonnes = 96;
    Grille grille(nbLignes, nbColonnes);

    // Demander le chemin du fichier
    std::string cheminFichier;
    std::cout << "Veuillez entrer le chemin du fichier de configuration : ";
    std::cin >> cheminFichier;

    // Charger la configuration depuis le fichier
    try {
        GestionFichier::chargerConfiguration(grille, cheminFichier);  // Charge la grille depuis le fichier
        std::cout << "Configuration chargée depuis : " << cheminFichier << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Erreur de chargement du fichier : " << e.what() << "\n";
        return 1;  // Si le fichier ne peut pas être chargé, sortir du programme
    }

    // Choisir le mode
    int modeChoisi = 0;
    while (modeChoisi != 1 && modeChoisi != 2) {
        std::cout << "Choisissez le mode :\n1 - Mode Console\n2 - Mode Graphique\n";
        std::cin >> modeChoisi;

        if (modeChoisi == 1) {
            ModeConsole modeConsole(grille);
            modeConsole.lancerSimulation();
        }
        else if (modeChoisi == 2) {
            int tailleCellule = 20; // Taille d'une cellule en pixels
            auto sfml = std::make_unique<SFMLInterface>(nbColonnes * tailleCellule, nbLignes * tailleCellule, tailleCellule);
            ModeGraphique modeGraphique(grille, std::move(sfml)); // La grille est passée ici après avoir été chargée
            modeGraphique.lancerSimulation();
        }
        else {
            std::cerr << "Mode invalide. Veuillez choisir entre 1 et 2.\n";
        }
    }

    // Sauvegarder la configuration dans le fichier
    try {
        GestionFichier::sauvegarderConfiguration(grille, cheminFichier);  // Sauvegarde la grille dans le fichier
        std::cout << "Configuration sauvegardée dans : " << cheminFichier << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Erreur de sauvegarde du fichier : " << e.what() << "\n";
        return 1;  // Si la sauvegarde échoue, sortir du programme
    }

    return 0;
}
