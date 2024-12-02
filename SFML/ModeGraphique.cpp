#include "ModeGraphique.h"
#include <SFML/Graphics.hpp>

// Constructeur de ModeGraphique
ModeGraphique::ModeGraphique(const Grille& grille, std::unique_ptr<SFMLInterface> interface)
    : ModeJeu(grille), interface(std::move(interface)) {
}

// Implémentation de lancerSimulation
void ModeGraphique::lancerSimulation() {
    // Boucle principale de simulation
    while (interface->estOuverte()) {
        // Afficher la grille dans l'interface
        interface->afficherGrille(grille);

        // Gérer les événements utilisateur (fermeture, clic, etc.)
        interface->attendreEvenements();

        // Calculer la prochaine itération
        grille.calculerProchaineIteration();
    }
}
