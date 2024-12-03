#ifndef SFMLINTERFACE_H
#define SFMLINTERFACE_H

#include <SFML/Graphics.hpp>
#include "Grille.h"

class SFMLInterface {
private:
    sf::RenderWindow window;
    sf::RectangleShape celluleShape;
    int tailleCellule;

public:
    SFMLInterface(int largeur, int hauteur, int tailleCellule); // Constructeur
    bool estOuverte() const;
    void afficherGrille(const Grille& grille);
    void attendreEvenements();
};

#endif // SFMLINTERFACE_H
