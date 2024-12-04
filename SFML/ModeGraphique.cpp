#include "ModeGraphique.h"
#include <SFML/Graphics.hpp>

// Constructeur de ModeGraphique
ModeGraphique::ModeGraphique(const Grille& grille, std::unique_ptr<SFMLInterface> interface)
    : ModeJeu(grille), interface(std::move(interface)), enPause(false) {
}
// Impl�mentation de lancerSimulation
void ModeGraphique::lancerSimulation() {
    int vitesseSimulation = 1000;  // 1000ms = 1 seconde
    sf::Clock clock;  // Horloge pour mesurer le temps �coul�

    // Boucle principale de simulation
    while (interface->estOuverte()) {
        interface->attendreEvenements(vitesseSimulation, enPause); // Passe l'�tat enPause pour mise � jour

        // Si la simulation est en pause, on saute la mise � jour de la grille
        if (enPause) {
            continue;
        }

        // V�rifier le temps �coul� pour avancer l'it�ration
        if (clock.getElapsedTime().asMilliseconds() >= vitesseSimulation) {
            interface->afficherGrille(grille); // Afficher la grille
            grille.calculerProchaineIteration(); // Calculer la prochaine it�ration
            clock.restart(); // R�initialiser l'horloge
        }
    }
}


