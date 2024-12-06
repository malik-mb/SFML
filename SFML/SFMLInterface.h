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
    sf::RectangleShape boutonStart;
    sf::RectangleShape boutonParams;
    sf::RectangleShape boutonTutorial;
    sf::RectangleShape boutonExit;

    sf::Texture zoomInTexture;
    sf::Texture zoomOutTexture;
    sf::Sprite zoomInSprite;
    sf::Sprite zoomOutSprite;

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

    sf::Vector2i derniereCelluleModifiee;
    bool estEnTrainDeModifier;

    const float BANDE_NOIRE_HAUTEUR = 100.0f;

public:
    SFMLInterface(int largeur, int hauteur, int tailleCellule);
    bool estOuverte() const;
    void afficherGrille(const Grille& grille);
    void afficherMenu();
    void attendreEvenements(int& vitesseSimulation, bool& enPause, Grille& grille);
    bool chargerPolice(const std::string& cheminFichier);
    void zoomIn();
    void zoomOut();
    bool estEnMenu() const { return enMenu; }
    void toggleMusic();
    void toggleCelluleAvecSouris(Grille& grille, const sf::Vector2i& mousePos);
};

#endif // SFMLINTERFACE_H