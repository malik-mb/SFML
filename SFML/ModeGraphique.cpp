#include "ModeGraphique.h"
#include <SFML/Graphics.hpp>

// Constructeur de ModeGraphique
ModeGraphique::ModeGraphique(const Grille& grille, std::unique_ptr<SFMLInterface> interface)
    : ModeJeu(grille), interface(std::move(interface)) {
}

// Implémentation de lancerSimulation
void ModeGraphique::lancerSimulation() {
    int vitesseSimulation = 1000;  // 1000ms = 1 seconde
    sf::Clock clock;  // Horloge pour mesurer le temps écoulé

    // Boucle principale de simulation
    while (interface->estOuverte()) {
        // Vérifier le temps écoulé pour savoir quand avancer l'itération
        if (clock.getElapsedTime().asMilliseconds() >= vitesseSimulation) {
            // Afficher la grille dans l'interface
            interface->afficherGrille(grille);

            // Gérer les événements utilisateur (fermeture, clic, etc.)
            interface->attendreEvenements(vitesseSimulation);

            // Calculer la prochaine itération
            grille.calculerProchaineIteration();

            // Réinitialiser l'horloge pour la prochaine itération
            clock.restart();
        }
    }
}


