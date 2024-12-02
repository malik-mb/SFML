#include "SFMLInterface.h"

SFMLInterface::SFMLInterface(int largeur, int hauteur) {
    window.create(sf::VideoMode(largeur, hauteur), "Simulation Graphique");
}

bool SFMLInterface::estOuverte() const {
    return window.isOpen();
}

void SFMLInterface::afficherGrille(const Grille& grille) {
    window.clear(sf::Color::Black);
    // Logique d'affichage des cellules de la grille (vivante/morte).
    window.display();
}

void SFMLInterface::attendreEvenements() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}
