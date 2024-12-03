#include "ModeGraphique.h"
#include <SFML/Graphics.hpp>

// Constructeur de ModeGraphique
ModeGraphique::ModeGraphique(const Grille& grille, std::unique_ptr<SFMLInterface> interface)
    : ModeJeu(grille), interface(std::move(interface)) {
}

// Impl�mentation de lancerSimulation
void ModeGraphique::lancerSimulation() {
    // Vitesse initiale de la simulation en millisecondes (1 seconde)
    int vitesseSimulation = 1000;  // 1000ms = 1 seconde
    sf::Clock clock;  // Horloge pour mesurer le temps �coul�

    // Boucle principale de simulation
    while (interface->estOuverte()) {
        // V�rifier le temps �coul� pour savoir quand avancer l'it�ration
        if (clock.getElapsedTime().asMilliseconds() >= vitesseSimulation) {
            // Afficher la grille dans l'interface
            interface->afficherGrille(grille);

            // G�rer les �v�nements utilisateur (fermeture, clic, etc.)
            interface->attendreEvenements(vitesseSimulation);

            // Calculer la prochaine it�ration
            grille.calculerProchaineIteration();

            // R�initialiser l'horloge pour la prochaine it�ration
            clock.restart();
        }

        // G�rer les entr�es clavier pour ajuster la vitesse de la simulation
        interface->attendreEvenements(vitesseSimulation);  // Attendre les �v�nements de la fen�tre

        // Fl�che droite (?) : augmenter la vitesse de la simulation de 200 ms
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            vitesseSimulation = std::max(vitesseSimulation - 200, 100);  // Min. 100ms
        }

        // Fl�che gauche (?) : diminuer la vitesse de la simulation de 200 ms
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            vitesseSimulation = std::min(vitesseSimulation + 200, 2000);  // Max. 2000ms
        }
    }
}

