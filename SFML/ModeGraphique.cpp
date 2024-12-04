#include "ModeGraphique.h"
#include <SFML/Graphics.hpp>

// Constructeur de ModeGraphique
ModeGraphique::ModeGraphique(const Grille& grille, std::unique_ptr<SFMLInterface> interface)
    : ModeJeu(grille), interface(std::move(interface)), enPause(false) {
}
// Implémentation de lancerSimulation
void ModeGraphique::lancerSimulation() {
    int vitesseSimulation = 1000;  // 1000ms = 1 seconde
    sf::Clock clock;  // Horloge pour mesurer le temps écoulé

    // Boucle principale de simulation
    while (interface->estOuverte()) {
        interface->attendreEvenements(vitesseSimulation, enPause); // Passe l'état enPause pour mise à jour

        // Si la simulation est en pause, on saute la mise à jour de la grille
        if (enPause) {
            continue;
        }

        // Vérifier le temps écoulé pour avancer l'itération
        if (clock.getElapsedTime().asMilliseconds() >= vitesseSimulation) {
            interface->afficherGrille(grille); // Afficher la grille
            grille.calculerProchaineIteration(); // Calculer la prochaine itération
            clock.restart(); // Réinitialiser l'horloge
        }
    }
}


