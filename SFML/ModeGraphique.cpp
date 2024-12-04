#include "ModeGraphique.h"
#include <SFML/Graphics.hpp>

// Constructeur de ModeGraphique
ModeGraphique::ModeGraphique(const Grille& grille, std::unique_ptr<SFMLInterface> interface)
    : ModeJeu(grille), interface(std::move(interface)), enPause(true) { // D�finir enPause sur true
}

// Impl�mentation de lancerSimulation
void ModeGraphique::lancerSimulation() {
    int vitesseSimulation = 1000;  // 1000ms = 1 seconde
    sf::Clock clock;  // Horloge pour mesurer le temps �coul�

    // Boucle principale de simulation
    while (interface->estOuverte()) {
        // Afficher la grille m�me si en pause
        interface->afficherGrille(grille);

        // G�rer les �v�nements utilisateur et l'�tat de pause
        interface->attendreEvenements(vitesseSimulation, enPause);

        // Si la simulation est en pause, ne pas avancer
        if (enPause) {
            continue;
        }

        // V�rifier le temps �coul� pour savoir quand avancer l'it�ration
        if (clock.getElapsedTime().asMilliseconds() >= vitesseSimulation) {
            // Calculer la prochaine it�ration
            grille.calculerProchaineIteration();

            // R�initialiser l'horloge pour la prochaine it�ration
            clock.restart();
        }
    }
}
