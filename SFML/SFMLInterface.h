#ifndef SFMLINTERFACE_H
#define SFMLINTERFACE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Grille.h"
#include <stack>
#include <vector>

class SFMLInterface {
private:
    sf::RenderWindow window;
    sf::RectangleShape celluleShape;
    int tailleCellule;
    bool enPleinEcran;
    bool musicPlaying;
    bool estEnTrainDeModifier;
    sf::Vector2i derniereCelluleModifiee;

    // Textures et sprites pour les boutons de zoom
    sf::Texture zoomInTexture;
    sf::Texture zoomOutTexture;
    sf::Sprite zoomInSprite;
    sf::Sprite zoomOutSprite;

    // Textures et sprites pour undo/redo
    sf::Texture undoTexture;
    sf::Texture redoTexture;
    sf::Sprite undoSprite;
    sf::Sprite redoSprite;

    // Textures et sprites pour pause/play
    sf::Texture pauseTexture;
    sf::Texture playTexture;
    sf::Sprite pauseSprite;
    sf::Sprite playSprite;

    // Police et textes
    sf::Font font;
    sf::Text messageTexte;
    sf::Text titreTexte;
    sf::Text startTexte;
    sf::Text paramsTexte;
    sf::Text tutorialTexte;
    sf::Text exitTexte;
    sf::Text musicTexte;

    // Boutons du menu
    sf::RectangleShape boutonStart;
    sf::RectangleShape boutonParams;
    sf::RectangleShape boutonTutorial;
    sf::RectangleShape boutonExit;

    // Musique
    sf::Music menuMusic;

    // Piles pour undo/redo
    std::stack<std::vector<std::vector<bool>>> undoStack;
    std::stack<std::vector<std::vector<bool>>> redoStack;

    static const int BANDE_NOIRE_HAUTEUR = 100;

    void sauvegarderEtat(const Grille& grille);
    std::vector<std::vector<bool>> captureEtatGrille(const Grille& grille);
    void appliquerEtatGrille(Grille& grille, const std::vector<std::vector<bool>>& etat);

public:
    bool enMenu;  // Ajout de cette ligne

    SFMLInterface(int largeur, int hauteur, int tailleCellule);
    void toggleMusic();
    void afficherMenu();
    void afficherGrille(const Grille& grille, bool enPause);
    void attendreEvenements(int& vitesseSimulation, bool& enPause, Grille& grille);
    void toggleCelluleAvecSouris(Grille& grille, const sf::Vector2i& mousePos);
    void zoomIn();
    void zoomOut();
    void undo(Grille& grille);
    void redo(Grille& grille);
    bool estOuverte() const;
    bool chargerPolice(const std::string& cheminFichier);
};

#endif