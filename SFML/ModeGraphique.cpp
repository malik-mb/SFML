#include "ModeGraphique.h"
#include <SFML/Graphics.hpp>

ModeGraphique::ModeGraphique(const Grille& grille, std::unique_ptr<SFMLInterface> interface)
    : ModeJeu(grille), interface(std::move(interface)), enPause(true) {
}

void ModeGraphique::lancerSimulation() {
    int vitesseSimulation = 1000;  // 1000ms = 1 seconde
    sf::Clock clock;

    while (interface->estOuverte()) {
        if (interface->enMenu) {
            interface->afficherMenu();
            interface->attendreEvenements(vitesseSimulation, enPause, grille);
            continue;
        }

        interface->afficherGrille(grille, enPause);
        interface->attendreEvenements(vitesseSimulation, enPause, grille);

        if (enPause) {
            continue;
        }

        if (clock.getElapsedTime().asMilliseconds() >= vitesseSimulation) {
            grille.calculerProchaineIteration();
            interface->incrementerMisesAJour();  // Incrémenter le compteur
            clock.restart();
        }
    }
}