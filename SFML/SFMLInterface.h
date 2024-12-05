#ifndef SFMLINTERFACE_H
#define SFMLINTERFACE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Grille.h"
#include <string>
#include <memory>

class SFMLInterface {
private:
    sf::RenderWindow window;
    sf::RectangleShape celluleShape;
    sf::RectangleShape boutonZoomIn;
    sf::RectangleShape boutonZoomOut;
    sf::RectangleShape boutonStart;
    sf::RectangleShape boutonParams;
    sf::RectangleShape boutonTutorial;
    sf::RectangleShape boutonExit;

    sf::Font font;
    sf::Text messageTexte;
    sf::Text startTexte;
    sf::Text paramsTexte;
    sf::Text tutorialTexte;
    sf::Text exitTexte;
    sf::Text titreTexte;
    sf::Text musicTexte;

    sf::Music menuMusic;
    bool musicPlaying;

    int tailleCellule;
    bool enPleinEcran;
    bool enMenu;

public:
    SFMLInterface(int largeur, int hauteur, int tailleCellule);
    bool estOuverte() const;
    void afficherGrille(const Grille& grille);
    void afficherMenu();
    void attendreEvenements(int& vitesseSimulation, bool& enPause);
    bool chargerPolice(const std::string& cheminFichier);
    void zoomIn();
    void zoomOut();
    bool estEnMenu() const { return enMenu; }
    void toggleMusic();
};

#endif // SFMLINTERFACE_H