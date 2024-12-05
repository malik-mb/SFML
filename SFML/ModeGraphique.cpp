#include "ModeGraphique.h"
#include <SFML/Graphics.hpp>

ModeGraphique::ModeGraphique(const Grille& grille, std::unique_ptr<SFMLInterface> interface)
    : ModeJeu(grille), interface(std::move(interface)), enPause(true) {
}

void ModeGraphique::lancerSimulation() {
    int vitesseSimulation = 1000;
    sf::Clock clock;

    while (interface->estOuverte()) {
        // Gestion du menu
        if (interface->estEnMenu()) {
            interface->afficherMenu();
            interface->attendreEvenements(vitesseSimulation, enPause);
            continue;
        }

        // Affichage de la grille
        interface->afficherGrille(grille);

        // Gestion des événements
        interface->attendreEvenements(vitesseSimulation, enPause);

        // Si en pause, ne pas mettre à jour la simulation
        if (enPause) {
            continue;
        }

        // Mise à jour de la simulation selon la vitesse
        if (clock.getElapsedTime().asMilliseconds() >= vitesseSimulation) {
            grille.calculerProchaineIteration();
            clock.restart();
        }
    }
}