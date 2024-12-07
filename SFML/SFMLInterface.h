#ifndef SFMLINTERFACE_H
#define SFMLINTERFACE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stack>
#include <vector>
#include <string>
#include "Grille.h"

class SFMLInterface {
private:
    static const int BANDE_NOIRE_HAUTEUR = 100;
    sf::RenderWindow window;
    sf::RectangleShape celluleShape;
    int tailleCellule;
    bool enPleinEcran;
    bool enMenu;
    bool enThemeMenu;
    bool musicPlaying;
    bool estEnTrainDeModifier;
    bool isMuted;
    int nombreIterations;
    sf::Vector2i derniereCelluleModifiee;
    float volume;
    float currentSpeed;
    size_t selectedMusic;
    static int generation;
    static int nombreMisesAJour;

    // Vecteurs pour la gestion des musiques
    std::vector<std::string> musicPaths;
    std::vector<std::string> musicNames;

    // Stacks pour undo/redo
    std::stack<std::vector<std::vector<bool>>> undoStack;
    std::stack<std::vector<std::vector<bool>>> redoStack;

    // Musique
    sf::Music menuMusic;

    // Police et textures
    sf::Font font;
    sf::Texture zoomInTexture, zoomOutTexture;
    sf::Texture undoTexture, redoTexture;
    sf::Texture pauseTexture, playTexture;
    sf::Texture resetTexture;
    sf::Texture oscillateurTexture, planeurTexture, canonTexture;
    sf::Texture muteTexture, soundTexture;
    sf::Texture speedTexture;
    sf::Texture triskelionTexture;

    // Sprites
    sf::Sprite triskelionSprite;
    sf::Sprite zoomInSprite, zoomOutSprite;
    sf::Sprite undoSprite, redoSprite;
    sf::Sprite pauseSprite, playSprite;
    sf::Sprite resetSprite;
    sf::Sprite oscillateurSprite, planeurSprite, canonSprite;
    sf::Sprite muteSprite, soundSprite;
    sf::Sprite speedSprite;

    // Textes
    sf::Text titreTexte;
    sf::Text populationTexte;
    sf::Text generationTexte;
    sf::Text oscillateurTexte, planeurTexte, canonTexte;
    sf::Text oscillateurNom, planeurNom, canonNom;
    sf::Text startTexte, paramsTexte, tutorialTexte, exitTexte;
    sf::Text musicTexte;

    // Contrôles de volume et vitesse
    sf::RectangleShape volumeBar, volumeSlider;
    sf::RectangleShape speedBar, speedSlider;

    // Boutons du menu
    sf::RectangleShape boutonStart;
    sf::RectangleShape boutonParams;
    sf::RectangleShape boutonTutorial;
    sf::RectangleShape boutonExit;

    // Méthodes privées
    void updateVolumeSlider();
    void updateSpeedSlider();
    void handleVolumeControl(const sf::Vector2i& mousePos);
    void handleSpeedControl(const sf::Vector2i& mousePos, int& vitesseSimulation);
    void ajouterPattern(Grille& grille, const std::vector<std::pair<int, int>>& coords, int ligneBase, int colonneBase);
    std::vector<std::vector<bool>> captureEtatGrille(const Grille& grille);
    void appliquerEtatGrille(Grille& grille, const std::vector<std::vector<bool>>& etat);
    void afficherThemeMenu();

public:
    SFMLInterface(int largeur, int hauteur, int tailleCellule);
    void afficherGrille(const Grille& grille, bool enPause);
    void afficherMenu();
    void attendreEvenements(int& vitesseSimulation, bool& enPause, Grille& grille);
    bool estOuverte() const;
    void zoomIn();
    void zoomOut();
    void toggleCelluleAvecSouris(Grille& grille, const sf::Vector2i& mousePos);
    void resetGrille(Grille& grille);
    void ajouterPlaneur(Grille& grille, int ligneBase, int colonneBase);
    void ajouterCanon(Grille& grille, int ligneBase, int colonneBase);
    void ajouterOscillateur(Grille& grille, int ligneBase, int colonneBase);
    void sauvegarderEtat(const Grille& grille);
    void undo(Grille& grille);
    void redo(Grille& grille);
    void resetGeneration();
    void toggleMusic();
    static void incrementerMisesAJour();
    static void resetMisesAJour();
    bool estEnMenu() const { return enMenu; }
};

#endif