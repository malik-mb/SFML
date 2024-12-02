#include "ModeGraphique.h"
#include <SFML/Graphics.hpp>

// Constructeur de ModeGraphique
ModeGraphique::ModeGraphique(const Grille& grille, std::unique_ptr<SFMLInterface> interface)
    : ModeJeu(grille), interface(std::move(interface)) {
}

// Impl�mentation de lancerSimulation
void ModeGraphique::lancerSimulation() {
    // Boucle principale de simulation
    while (interface->estOuverte()) {
        // Afficher la grille dans l'interface
        interface->afficherGrille(grille);

        // G�rer les �v�nements utilisateur (fermeture, clic, etc.)
        interface->attendreEvenements();

        // Calculer la prochaine it�ration
        grille.calculerProchaineIteration();
    }
}
