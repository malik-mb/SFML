#include "ModeConsole.h"
#include <iostream>
#include <thread>
#include <chrono>

ModeConsole::ModeConsole(Grille grille) : ModeJeu(grille) {}

void ModeConsole::lancerSimulation() {
    int vitesse, iterations;
    std::cout << "Choisissez la vitesse (en millisecondes entre chaque itération) : ";
    std::cin >> vitesse;
    std::cout << "Choisissez le nombre d'itérations : ";
    std::cin >> iterations;

    const std::string dossier = "MK14_oZutE";
    GestionFichier gestionFichier;

    // Créer le dossier MK14
    creerDossier(dossier);

    for (int i = 1; i <= iterations; ++i) {
        grille.afficherEtat(); // Afficher la grille
        gestionFichier.sauvegarderIteration(grille, dossier, i); // Sauvegarder l'état

        grille.calculerProchaineIteration(); // Passer à la prochaine itération

        std::cout << "Iteration " << i << " terminée.\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(vitesse)); // Pause entre itérations
    }

    std::cout << "Simulation terminée. Résultats sauvegardés dans le dossier '" << dossier << "'.\n";
}
