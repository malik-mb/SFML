#ifndef SFMLINTERFACE_H
#define SFMLINTERFACE_H

#include <SFML/Graphics.hpp>
#include "Grille.h"

class SFMLInterface {
private:
    sf::RenderWindow window;
    sf::RectangleShape celluleShape;
    sf::RectangleShape boutonZoomIn;
    sf::RectangleShape boutonZoomOut;
    sf::Font font; // Police pour le texte
    sf::Text messageTexte; // Texte affich� en bas
    int tailleCellule;
    bool enPleinEcran;  // Variable pour savoir si la fen�tre est en plein �cran ou pas
public:
    SFMLInterface(int largeur, int hauteur, int tailleCellule); // Constructeur
    bool estOuverte() const;
    void afficherGrille(const Grille& grille);
    // D�claration modifi�e de la fonction pour accepter un argument `int&`
    void attendreEvenements(int& vitesseSimulation, bool& enPause);
    bool chargerPolice(const std::string& cheminFichier);
    void zoomIn();
    void zoomOut();
};

#endif // SFMLINTERFACE_H
