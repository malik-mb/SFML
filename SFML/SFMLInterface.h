#ifndef SFMLINTERFACE_H
#define SFMLINTERFACE_H

#include <SFML/Graphics.hpp>
#include "Grille.h"

class SFMLInterface {
private:
    sf::RenderWindow window;
    sf::RectangleShape celluleShape;
    sf::Font font; // Police pour le texte
    sf::Text messageTexte; // Texte affiché en bas
    int tailleCellule;

public:
    SFMLInterface(int largeur, int hauteur, int tailleCellule); // Constructeur
    bool estOuverte() const;
    void afficherGrille(const Grille& grille);
    // Déclaration modifiée de la fonction pour accepter un argument `int&`
    void attendreEvenements(int& vitesseSimulation, bool& enPause);
    bool chargerPolice(const std::string& cheminFichier);
};

#endif // SFMLINTERFACE_H
