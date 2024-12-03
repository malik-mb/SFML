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
    // D�claration modifi�e de la fonction pour accepter un argument `int&`
    void attendreEvenements(int& vitesseSimulation);  // Ajouter l'argument ici

};

#endif // SFMLINTERFACE_H
