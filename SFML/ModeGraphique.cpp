#include "ModeGraphique.h"
#include <SFML/Graphics.hpp>

// Constructeur de ModeGraphique
ModeGraphique::ModeGraphique(const Grille& grille, std::unique_ptr<SFMLInterface> interface)
    : ModeJeu(grille), interface(std::move(interface)) {
}

// Impl�mentation de lancerSimulation
void ModeGraphique::lancerSimulation() {
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
    }
}


