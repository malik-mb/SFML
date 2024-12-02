#include "ModeConsole.h"
#include <iostream>
#include <thread>
#include <chrono>

ModeConsole::ModeConsole(Grille grille) : ModeJeu(grille) {}

void ModeConsole::lancerSimulation() {
    int vitesse, iterations;
    std::cout << "Choisissez la vitesse (en millisecondes entre chaque it�ration) : ";
    std::cin >> vitesse;
    std::cout << "Choisissez le nombre d'it�rations : ";
    std::cin >> iterations;

    const std::string dossier = "MK14_oZutE";
    GestionFichier gestionFichier;

    // Cr�er le dossier MK14
    creerDossier(dossier);

    for (int i = 1; i <= iterations; ++i) {
        grille.afficherEtat(); // Afficher la grille
        gestionFichier.sauvegarderIteration(grille, dossier, i); // Sauvegarder l'�tat

        grille.calculerProchaineIteration(); // Passer � la prochaine it�ration

        std::cout << "Iteration " << i << " termin�e.\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(vitesse)); // Pause entre it�rations
    }

    std::cout << "Simulation termin�e. R�sultats sauvegard�s dans le dossier '" << dossier << "'.\n";
}
