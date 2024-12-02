#ifndef SFMLINTERFACE_H
#define SFMLINTERFACE_H

#include <SFML/Graphics.hpp>
#include "Grille.h"

class SFMLInterface {
private:
    sf::RenderWindow window;

public:
    SFMLInterface(int largeur, int hauteur); // Constructeur
    bool estOuverte() const;
    void afficherGrille(const Grille& grille);
    void attendreEvenements();
};

#endif // SFMLINTERFACE_H
