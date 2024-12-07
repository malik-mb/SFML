#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Grille.h"
#include <stack>

class SFMLInterface {
private:
    sf::RenderWindow window;
    sf::RectangleShape celluleShape;
    sf::Font font;
    sf::Text messageTexte;
    sf::Text titreTexte;
    sf::Text musicTexte;
    sf::Text startTexte;
    sf::Text paramsTexte;
    sf::Text tutorialTexte;
    sf::Text exitTexte;
    sf::Text oscillateurTexte;
    sf::Text planeurTexte;
    sf::Text canonTexte;
    sf::Text oscillateurNom;
    sf::Text planeurNom;
    sf::Text canonNom;
    sf::Text populationTexte;
    sf::Text generationTexte;

    sf::RectangleShape boutonStart;
    sf::RectangleShape boutonParams;
    sf::RectangleShape boutonTutorial;
    sf::RectangleShape boutonExit;

    sf::Texture zoomInTexture;
    sf::Texture zoomOutTexture;
    sf::Texture undoTexture;
    sf::Texture redoTexture;
    sf::Texture pauseTexture;
    sf::Texture playTexture;
    sf::Texture resetTexture;
    sf::Texture oscillateurTexture;
    sf::Texture planeurTexture;
    sf::Texture canonTexture;
    sf::Texture muteTexture;
    sf::Texture soundTexture;
    sf::Texture speedTexture;

    sf::Sprite zoomInSprite;
    sf::Sprite zoomOutSprite;
    sf::Sprite undoSprite;
    sf::Sprite redoSprite;
    sf::Sprite pauseSprite;
    sf::Sprite playSprite;
    sf::Sprite resetSprite;
    sf::Sprite oscillateurSprite;
    sf::Sprite planeurSprite;
    sf::Sprite canonSprite;
    sf::Sprite muteSprite;
    sf::Sprite soundSprite;
    sf::Sprite speedSprite;

    sf::RectangleShape volumeBar;
    sf::RectangleShape volumeSlider;
    sf::RectangleShape speedBar;
    sf::RectangleShape speedSlider;

    sf::Music menuMusic;
    bool musicPlaying;
    float volume;
    bool isMuted;
    float currentSpeed;

    int tailleCellule;
    bool enPleinEcran;
    bool estEnTrainDeModifier;
    sf::Vector2i derniereCelluleModifiee;
    static int generation;
    int nombreIterations;  // Variable pour stocker
    std::stack<std::vector<std::vector<bool>>> undoStack;
    std::stack<std::vector<std::vector<bool>>> redoStack;

    static const int BANDE_NOIRE_HAUTEUR = 100;
     static int nombreMisesAJour;  // Pour compter les mises à jour
    void updateVolumeSlider();
    void updateSpeedSlider();
    void handleVolumeControl(const sf::Vector2i& mousePos);
    void handleSpeedControl(const sf::Vector2i& mousePos, int& vitesseSimulation);
    void ajouterPattern(Grille& grille, const std::vector<std::pair<int, int>>& coords, int ligneBase, int colonneBase);
    void resetGrille(Grille& grille);
    void ajouterPlaneur(Grille& grille, int ligneBase, int colonneBase);
    void ajouterCanon(Grille& grille, int ligneBase, int colonneBase);
    void ajouterOscillateur(Grille& grille, int ligneBase, int colonneBase);
    void resetGeneration();

public:
    bool enMenu;
    void setNombreIterations(int n) { nombreIterations = n; }
    void resetNombreIterations() { nombreIterations = 0; }
    SFMLInterface(int largeur, int hauteur, int tailleCellule);
    void afficherGrille(const Grille& grille, bool enPause);
    void afficherMenu();
    void attendreEvenements(int& vitesseSimulation, bool& enPause, Grille& grille);
    bool estOuverte() const;
    void toggleMusic();
    void zoomIn();
    void zoomOut();
    bool chargerPolice(const std::string& cheminFichier);
    void sauvegarderEtat(const Grille& grille);
    void undo(Grille& grille);
    void redo(Grille& grille);
    std::vector<std::vector<bool>> captureEtatGrille(const Grille& grille);
    void appliquerEtatGrille(Grille& grille, const std::vector<std::vector<bool>>& etat);
    void toggleCelluleAvecSouris(Grille& grille, const sf::Vector2i& mousePos);
    void incrementerMisesAJour();
    void resetMisesAJour();

};