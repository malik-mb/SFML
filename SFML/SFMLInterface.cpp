#include "SFMLInterface.h"

SFMLInterface::SFMLInterface(int largeur, int hauteur, int tailleCellule)
    : tailleCellule(tailleCellule) {
    window.create(sf::VideoMode(largeur, hauteur), "Simulation Graphique");
    celluleShape.setSize(sf::Vector2f(tailleCellule - 1, tailleCellule - 1)); // Légèrement plus petit pour un effet de grille
}

bool SFMLInterface::estOuverte() const {
    return window.isOpen();
}

void SFMLInterface::afficherGrille(const Grille& grille) {
    window.clear(sf::Color(50, 50, 50)); // Fond gris foncé

    for (int i = 0; i < grille.getNbLignes(); ++i) {
        for (int j = 0; j < grille.getNbColonnes(); ++j) {
            if (grille.getCellule(i, j).estVivante()) {
                celluleShape.setFillColor(sf::Color(255, 105, 180)); // Rose vif
            }
            else {
                celluleShape.setFillColor(sf::Color(200, 200, 200)); // Gris clair
            }
            celluleShape.setPosition(j * tailleCellule, i * tailleCellule);
            window.draw(celluleShape);
        }
    }

    window.display();
}

void SFMLInterface::attendreEvenements() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}
