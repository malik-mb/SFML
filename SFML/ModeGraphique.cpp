#include "ModeGraphique.h"
#include <SFML/Graphics.hpp>

// Constructeur de ModeGraphique
ModeGraphique::ModeGraphique(const Grille& grille, std::unique_ptr<SFMLInterface> interface)
    : ModeJeu(grille), interface(std::move(interface)) {
}

// Implémentation de lancerSimulation
void ModeGraphique::lancerSimulation() {
    // Vitesse initiale de la simulation en millisecondes (1 seconde)
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

        // Gérer les entrées clavier pour ajuster la vitesse de la simulation
        interface->attendreEvenements(vitesseSimulation);  // Attendre les événements de la fenêtre

        // Flèche droite (?) : augmenter la vitesse de la simulation de 200 ms
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            vitesseSimulation = std::max(vitesseSimulation - 200, 100);  // Min. 100ms
        }

        // Flèche gauche (?) : diminuer la vitesse de la simulation de 200 ms
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            vitesseSimulation = std::min(vitesseSimulation + 200, 2000);  // Max. 2000ms
        }
    }
}

