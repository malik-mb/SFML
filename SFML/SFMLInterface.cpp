#include "SFMLInterface.h"
#include <stdexcept>
#include <iostream>

// Initialisation de la variable statique
int SFMLInterface::generation = 0;
int SFMLInterface::nombreMisesAJour = 0;
void SFMLInterface::incrementerMisesAJour() {
    nombreMisesAJour++;
}

void SFMLInterface::resetMisesAJour() {
    nombreMisesAJour = 0;
}

SFMLInterface::SFMLInterface(int largeur, int hauteur, int tailleCellule)
    : tailleCellule(tailleCellule), enPleinEcran(true), enMenu(true), musicPlaying(false),
    estEnTrainDeModifier(false), nombreIterations(0),derniereCelluleModifiee(-1, -1), volume(50.0f), isMuted(false), currentSpeed(50.0f) {

    window.create(sf::VideoMode::getDesktopMode(), "Jeu de la Vie", sf::Style::Fullscreen);
    celluleShape.setSize(sf::Vector2f(tailleCellule - 1, tailleCellule - 1));

    if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        std::cerr << "Erreur : Impossible de charger la police." << std::endl;
    }

    // Chargement des textures
    if (!zoomInTexture.loadFromFile("C:\\Users\\malik\\Music\\icons8-zoomer-48.png")) {
        std::cerr << "Erreur : Impossible de charger l'icône de zoom in" << std::endl;
    }
    if (!zoomOutTexture.loadFromFile("C:\\Users\\malik\\Music\\icons8-dézoomer-48.png")) {
        std::cerr << "Erreur : Impossible de charger l'icône de zoom out" << std::endl;
    }
    if (!undoTexture.loadFromFile("C:\\Users\\malik\\Music\\icons8-gauche-2-50.png")) {
        std::cerr << "Erreur : Impossible de charger l'icône undo" << std::endl;
    }
    if (!redoTexture.loadFromFile("C:\\Users\\malik\\Music\\icons8-droit-2-60.png")) {
        std::cerr << "Erreur : Impossible de charger l'icône redo" << std::endl;
    }
    if (!pauseTexture.loadFromFile("C:\\Users\\malik\\Music\\icons8-pause-48.png")) {
        std::cerr << "Erreur : Impossible de charger l'icône de pause" << std::endl;
    }
    if (!playTexture.loadFromFile("C:\\Users\\malik\\Music\\icons8-lecture-50.png")) {
        std::cerr << "Erreur : Impossible de charger l'icône de play" << std::endl;
    }
    if (!resetTexture.loadFromFile("C:\\Users\\malik\\Music\\icons8-mises-à-jour-disponibles-50.png")) {
        std::cerr << "Erreur : Impossible de charger l'icône de reset" << std::endl;
    }
    if (!oscillateurTexture.loadFromFile("C:\\Users\\malik\\Music\\oss.png")) {
        std::cerr << "Erreur : Impossible de charger l'image de l'oscillateur" << std::endl;
    }
    if (!planeurTexture.loadFromFile("C:\\Users\\malik\\Music\\plan.png")) {
        std::cerr << "Erreur : Impossible de charger l'image du planeur" << std::endl;
    }
    if (!canonTexture.loadFromFile("C:\\Users\\malik\\Music\\canon.png")) {
        std::cerr << "Erreur : Impossible de charger l'image du canon" << std::endl;
    }
    if (!muteTexture.loadFromFile("C:\\Users\\malik\\Music\\icons8-muet-64.png")) {
        std::cerr << "Erreur : Impossible de charger l'icône mute" << std::endl;
    }
    if (!soundTexture.loadFromFile("C:\\Users\\malik\\Music\\icons8-son-64.png")) {
        std::cerr << "Erreur : Impossible de charger l'icône son" << std::endl;
    }
    if (!speedTexture.loadFromFile("C:\\Users\\malik\\Music\\icons8-éclair-48.png")) {
        std::cerr << "Erreur : Impossible de charger l'icône de vitesse" << std::endl;
    }    // Configuration des sprites
    zoomInSprite.setTexture(zoomInTexture);
    zoomOutSprite.setTexture(zoomOutTexture);
    undoSprite.setTexture(undoTexture);
    redoSprite.setTexture(redoTexture);
    pauseSprite.setTexture(pauseTexture);
    playSprite.setTexture(playTexture);
    resetSprite.setTexture(resetTexture);
    oscillateurSprite.setTexture(oscillateurTexture);
    planeurSprite.setTexture(planeurTexture);
    canonSprite.setTexture(canonTexture);
    muteSprite.setTexture(muteTexture);
    soundSprite.setTexture(soundTexture);
    speedSprite.setTexture(speedTexture);

    // Redimensionnement des sprites
    float patternSize = 40.0f;
    float scale;

    scale = patternSize / oscillateurSprite.getGlobalBounds().width;
    oscillateurSprite.setScale(scale, scale);
    scale = patternSize / planeurSprite.getGlobalBounds().width;
    planeurSprite.setScale(scale, scale);
    scale = patternSize / canonSprite.getGlobalBounds().width;
    canonSprite.setScale(scale, scale);

    // Redimensionner les icônes de son et de vitesse
    float iconSize = 30.0f;
    scale = iconSize / muteSprite.getGlobalBounds().width;
    muteSprite.setScale(scale, scale);
    scale = iconSize / soundSprite.getGlobalBounds().width;
    soundSprite.setScale(scale, scale);
    scale = iconSize / speedSprite.getGlobalBounds().width;
    speedSprite.setScale(scale, scale);

    // Configuration des barres de volume et de vitesse
    float barWidth = 100.0f;
    float barHeight = 5.0f;
    float sliderSize = 10.0f;

    volumeBar.setSize(sf::Vector2f(barWidth, barHeight));
    volumeBar.setFillColor(sf::Color(100, 100, 100));
    volumeSlider.setSize(sf::Vector2f(sliderSize, sliderSize));
    volumeSlider.setFillColor(sf::Color::White);

    speedBar.setSize(sf::Vector2f(barWidth, barHeight));
    speedBar.setFillColor(sf::Color(100, 100, 100));
    speedSlider.setSize(sf::Vector2f(sliderSize, sliderSize));
    speedSlider.setFillColor(sf::Color::White);

    // Positionnement des éléments
    float spacing = 20.0f;
    float startX = spacing;
    float patternY = window.getSize().y - BANDE_NOIRE_HAUTEUR / 2 - patternSize / 2;
    float spacingPatterns = 120.0f;
    float controlsY = window.getSize().y - BANDE_NOIRE_HAUTEUR / 2;

    // Position des patterns
    oscillateurSprite.setPosition(startX, patternY);
    planeurSprite.setPosition(startX + spacingPatterns, patternY);
    canonSprite.setPosition(startX + spacingPatterns * 2, patternY);
    resetSprite.setPosition(startX + spacingPatterns * 3, patternY);

    // Configuration des textes de population et génération
    populationTexte.setFont(font);
    populationTexte.setCharacterSize(20);
    populationTexte.setFillColor(sf::Color::White);
    populationTexte.setPosition(
        speedSprite.getPosition().x + 1150,  // Avant le contrôle de vitesse
        controlsY - 10
    );

    generationTexte.setFont(font);
    generationTexte.setCharacterSize(20);
    generationTexte.setFillColor(sf::Color::White);
    generationTexte.setPosition(
        resetSprite.getPosition().x + resetSprite.getGlobalBounds().width + 100,  // Après l'icône reset
        controlsY - 10
    );
    // Configuration des noms des patterns
    oscillateurNom.setFont(font);
    oscillateurNom.setString("Oscillateur");
    oscillateurNom.setCharacterSize(12);
    oscillateurNom.setFillColor(sf::Color::White);
    oscillateurNom.setPosition(
        oscillateurSprite.getPosition().x,
        oscillateurSprite.getPosition().y - 20
    );

    planeurNom.setFont(font);
    planeurNom.setString("Planeur");
    planeurNom.setCharacterSize(12);
    planeurNom.setFillColor(sf::Color::White);
    planeurNom.setPosition(
        planeurSprite.getPosition().x,
        planeurSprite.getPosition().y - 20
    );

    canonNom.setFont(font);
    canonNom.setString("Canon");
    canonNom.setCharacterSize(12);
    canonNom.setFillColor(sf::Color::White);
    canonNom.setPosition(
        canonSprite.getPosition().x,
        canonSprite.getPosition().y - 20
    );

    // Position des contrôles à droite
    float rightMargin = spacing;

    zoomOutSprite.setPosition(
        window.getSize().x - zoomOutSprite.getGlobalBounds().width - rightMargin,
        controlsY - zoomOutSprite.getGlobalBounds().height / 2
    );

    zoomInSprite.setPosition(
        zoomOutSprite.getPosition().x - zoomInSprite.getGlobalBounds().width - rightMargin,
        controlsY - zoomInSprite.getGlobalBounds().height / 2
    );

    volumeBar.setPosition(
        zoomInSprite.getPosition().x - volumeBar.getSize().x - rightMargin * 2,
        controlsY
    );

    soundSprite.setPosition(
        volumeBar.getPosition().x - soundSprite.getGlobalBounds().width - rightMargin,
        controlsY - soundSprite.getGlobalBounds().height / 2
    );

    muteSprite.setPosition(soundSprite.getPosition());

    speedBar.setPosition(
        soundSprite.getPosition().x - speedBar.getSize().x - rightMargin * 2,
        controlsY
    );

    speedSprite.setPosition(
        speedBar.getPosition().x - speedSprite.getGlobalBounds().width - rightMargin,
        controlsY - speedSprite.getGlobalBounds().height / 2
    );

    // Position des contrôles au centre
    float centerX = window.getSize().x / 2;

    undoSprite.setPosition(
        centerX - undoSprite.getGlobalBounds().width - spacing * 2,
        controlsY - undoSprite.getGlobalBounds().height / 2
    );

    pauseSprite.setPosition(
        centerX - pauseSprite.getGlobalBounds().width / 2,
        controlsY - pauseSprite.getGlobalBounds().height / 2
    );

    playSprite.setPosition(
        centerX - playSprite.getGlobalBounds().width / 2,
        controlsY - playSprite.getGlobalBounds().height / 2
    );

    redoSprite.setPosition(
        centerX + spacing * 2,
        controlsY - redoSprite.getGlobalBounds().height / 2
    );

    // Configuration des textes des raccourcis
    oscillateurTexte.setFont(font);
    oscillateurTexte.setString("Press O");
    oscillateurTexte.setCharacterSize(12);
    oscillateurTexte.setFillColor(sf::Color::White);
    oscillateurTexte.setPosition(
        oscillateurSprite.getPosition().x,
        oscillateurSprite.getPosition().y + oscillateurSprite.getGlobalBounds().height + 5
    );
    planeurTexte.setFont(font);
    planeurTexte.setString("Press P");
    planeurTexte.setCharacterSize(12);
    planeurTexte.setFillColor(sf::Color::White);
    planeurTexte.setPosition(
        planeurSprite.getPosition().x,
        planeurSprite.getPosition().y + planeurSprite.getGlobalBounds().height + 5
    );

    canonTexte.setFont(font);
    canonTexte.setString("Press C");
    canonTexte.setCharacterSize(12);
    canonTexte.setFillColor(sf::Color::White);
    canonTexte.setPosition(
        canonSprite.getPosition().x,
        canonSprite.getPosition().y + canonSprite.getGlobalBounds().height + 5
    );

    updateVolumeSlider();
    updateSpeedSlider();

    // Configuration de la musique
    try {
        if (menuMusic.openFromFile("C:\\Users\\malik\\Downloads\\PNL-Onizuka-_Instrumental_-Instrumentals.ogg")) {
            menuMusic.setLoop(true);
            menuMusic.setVolume(volume);
            menuMusic.play();
            musicPlaying = true;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Erreur lors du chargement de la musique : " << e.what() << std::endl;
    }

    // Configuration du menu
    titreTexte.setFont(font);
    titreTexte.setString("Jeu de la Vie");
    titreTexte.setCharacterSize(50);
    titreTexte.setFillColor(sf::Color::White);
    titreTexte.setPosition(
        (window.getSize().x - titreTexte.getLocalBounds().width) / 2,
        window.getSize().y / 4
    );

    const float boutonLargeur = 200;
    const float boutonHauteur = 60;
    const float espacementBoutons = 20;
    const float centreX = window.getSize().x / 2;
    const float premierBoutonY = window.getSize().y / 2;

    boutonStart.setSize(sf::Vector2f(boutonLargeur, boutonHauteur));
    boutonStart.setFillColor(sf::Color(50, 150, 50));
    boutonStart.setPosition(centreX - boutonLargeur / 2, premierBoutonY);

    boutonParams.setSize(sf::Vector2f(boutonLargeur, boutonHauteur));
    boutonParams.setFillColor(sf::Color(50, 150, 50));
    boutonParams.setPosition(centreX - boutonLargeur / 2, premierBoutonY + boutonHauteur + espacementBoutons);

    boutonTutorial.setSize(sf::Vector2f(boutonLargeur, boutonHauteur));
    boutonTutorial.setFillColor(sf::Color(50, 150, 50));
    boutonTutorial.setPosition(centreX - boutonLargeur / 2, premierBoutonY + (boutonHauteur + espacementBoutons) * 2);

    boutonExit.setSize(sf::Vector2f(boutonLargeur, boutonHauteur));
    boutonExit.setFillColor(sf::Color(50, 150, 50));
    boutonExit.setPosition(centreX - boutonLargeur / 2, premierBoutonY + (boutonHauteur + espacementBoutons) * 3);

    startTexte.setFont(font);
    startTexte.setString("START");
    startTexte.setCharacterSize(30);
    startTexte.setFillColor(sf::Color::White);
    startTexte.setPosition(
        centreX - startTexte.getLocalBounds().width / 2,
        premierBoutonY + (boutonHauteur - startTexte.getLocalBounds().height) / 2
    );

    paramsTexte.setFont(font);
    paramsTexte.setString("PARAMETRES");
    paramsTexte.setCharacterSize(30);
    paramsTexte.setFillColor(sf::Color::White);
    paramsTexte.setPosition(
        centreX - paramsTexte.getLocalBounds().width / 2,
        premierBoutonY + boutonHauteur + espacementBoutons + (boutonHauteur - paramsTexte.getLocalBounds().height) / 2
    );
    tutorialTexte.setFont(font);
    tutorialTexte.setString("TUTORIAL");
    tutorialTexte.setCharacterSize(30);
    tutorialTexte.setFillColor(sf::Color::White);
    tutorialTexte.setPosition(
        centreX - tutorialTexte.getLocalBounds().width / 2,
        premierBoutonY + (boutonHauteur + espacementBoutons) * 2 + (boutonHauteur - tutorialTexte.getLocalBounds().height) / 2
    );

    exitTexte.setFont(font);
    exitTexte.setString("EXIT");
    exitTexte.setCharacterSize(30);
    exitTexte.setFillColor(sf::Color::White);
    exitTexte.setPosition(
        centreX - exitTexte.getLocalBounds().width / 2,
        premierBoutonY + (boutonHauteur + espacementBoutons) * 3 + (boutonHauteur - exitTexte.getLocalBounds().height) / 2
    );
}

void SFMLInterface::afficherGrille(const Grille& grille, bool enPause) {
    window.clear(sf::Color(50, 50, 50));

    int hauteurGrille = window.getSize().y - BANDE_NOIRE_HAUTEUR;

    // Dessiner la grille
    for (int i = 0; i < grille.getNbLignes(); ++i) {
        for (int j = 0; j < grille.getNbColonnes(); ++j) {
            if (i * tailleCellule < hauteurGrille) {
                sf::VertexArray quad(sf::Quads, 4);
                float x = static_cast<float>(j * tailleCellule);
                float y = static_cast<float>(i * tailleCellule);
                float size = static_cast<float>(tailleCellule - 1);

                if (grille.getCellule(i, j).estVivante()) {
                    // Cellule vivante : Dégradé #009dff ↔ #00d5ff
                    quad[0].color = sf::Color(0, 200, 255);   // #009dff (bleu vif)
                    quad[1].color = sf::Color(0, 255, 255);   // #00d5ff (bleu clair)
                    quad[2].color = sf::Color(0, 255, 255);   // #00d5ff (bleu clair)
                    quad[3].color = sf::Color(0, 200, 255);   // #009dff (bleu vif)
                }
                else {
                    // Cellule morte : Dégradé #0b0d0e ↔ #141014
                    quad[0].color = sf::Color(11, 13, 14);  // #0b0d0e (gris sombre bleuté)
                    quad[1].color = sf::Color(20, 16, 20);  // #141014 (gris-noir)
                    quad[2].color = sf::Color(20, 16, 20);  // #141014 (gris-noir)
                    quad[3].color = sf::Color(11, 13, 14);  // #0b0d0e (gris sombre bleuté)
                }

                quad[0].position = sf::Vector2f(x, y);
                quad[1].position = sf::Vector2f(x + size, y);
                quad[2].position = sf::Vector2f(x + size, y + size);
                quad[3].position = sf::Vector2f(x, y + size);

                window.draw(quad);
            }
        }
    }

    // Calculer et mettre à jour la population
    int population = 0;
    for (int i = 0; i < grille.getNbLignes(); ++i) {
        for (int j = 0; j < grille.getNbColonnes(); ++j) {
            if (grille.getCellule(i, j).estVivante()) {
                population++;
            }
        }
    }
    populationTexte.setString("Population: " + std::to_string(population));

    // Mettre à jour le compteur de générations
    if (!enPause) {
        generation++;
    }
    generationTexte.setString("Nombre d'iterations: " + std::to_string(nombreMisesAJour));

    // Dessiner la bande noire
    sf::RectangleShape bandeNoire(sf::Vector2f(static_cast<float>(window.getSize().x), BANDE_NOIRE_HAUTEUR));
    bandeNoire.setPosition(0, static_cast<float>(window.getSize().y - BANDE_NOIRE_HAUTEUR));
    bandeNoire.setFillColor(sf::Color::Black);
    window.draw(bandeNoire);
    // Dessiner tous les éléments de l'interface
    window.draw(oscillateurSprite);
    window.draw(planeurSprite);
    window.draw(canonSprite);
    window.draw(resetSprite);

    // Dessiner les noms des patterns
    window.draw(oscillateurNom);
    window.draw(planeurNom);
    window.draw(canonNom);

    // Dessiner les raccourcis
    window.draw(oscillateurTexte);
    window.draw(planeurTexte);
    window.draw(canonTexte);

    // Dessiner les contrôles
    window.draw(zoomInSprite);
    window.draw(zoomOutSprite);
    window.draw(undoSprite);
    window.draw(redoSprite);

    // Dessiner les contrôles de volume
    window.draw(volumeBar);
    window.draw(volumeSlider);
    window.draw(isMuted ? muteSprite : soundSprite);

    // Dessiner les contrôles de vitesse
    window.draw(speedBar);
    window.draw(speedSlider);
    window.draw(speedSprite);

    // Dessiner la population et la génération
    window.draw(populationTexte);
    window.draw(generationTexte);

    // Dessiner le bouton play/pause
    if (enPause) {
        window.draw(playSprite);
    }
    else {
        window.draw(pauseSprite);
    }

    window.display();
}

void SFMLInterface::afficherMenu() {
    window.clear(sf::Color(30, 30, 30));

    window.draw(titreTexte);

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    auto gererSurvol = [&](sf::RectangleShape& bouton) {
        if (bouton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            bouton.setFillColor(sf::Color(70, 170, 70));
        }
        else {
            bouton.setFillColor(sf::Color(50, 150, 50));
        }
        };

    gererSurvol(boutonStart);
    gererSurvol(boutonParams);
    gererSurvol(boutonTutorial);
    gererSurvol(boutonExit);

    window.draw(boutonStart);
    window.draw(startTexte);
    window.draw(boutonParams);
    window.draw(paramsTexte);
    window.draw(boutonTutorial);
    window.draw(tutorialTexte);
    window.draw(boutonExit);
    window.draw(exitTexte);
    window.draw(musicTexte);

    window.display();
}

void SFMLInterface::resetGeneration() {
    generation = 0;
}

void SFMLInterface::updateVolumeSlider() {
    float sliderX = volumeBar.getPosition().x + (volume / 100.0f) * volumeBar.getSize().x - volumeSlider.getSize().x / 2;
    float sliderY = volumeBar.getPosition().y - volumeSlider.getSize().y / 2 + volumeBar.getSize().y / 2;
    volumeSlider.setPosition(sliderX, sliderY);
}

void SFMLInterface::updateSpeedSlider() {
    float sliderX = speedBar.getPosition().x + (currentSpeed / 100.0f) * speedBar.getSize().x - speedSlider.getSize().x / 2;
    float sliderY = speedBar.getPosition().y - speedSlider.getSize().y / 2 + speedBar.getSize().y / 2;
    speedSlider.setPosition(sliderX, sliderY);
}
void SFMLInterface::handleVolumeControl(const sf::Vector2i& mousePos) {
    if (volumeBar.getGlobalBounds().contains(mousePos.x, mousePos.y) ||
        volumeSlider.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        float relativeX = mousePos.x - volumeBar.getPosition().x;
        volume = (relativeX / volumeBar.getSize().x) * 100;
        volume = std::max(0.0f, std::min(100.0f, volume));
        menuMusic.setVolume(isMuted ? 0 : volume);
        updateVolumeSlider();
    }
}

void SFMLInterface::handleSpeedControl(const sf::Vector2i& mousePos, int& vitesseSimulation) {
    if (speedBar.getGlobalBounds().contains(mousePos.x, mousePos.y) ||
        speedSlider.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        float relativeX = mousePos.x - speedBar.getPosition().x;
        currentSpeed = (relativeX / speedBar.getSize().x) * 100;
        currentSpeed = std::max(0.0f, std::min(100.0f, currentSpeed));
        vitesseSimulation = 2000 - ((currentSpeed / 100.0f) * 1950);
        updateSpeedSlider();
    }
}

void SFMLInterface::toggleMusic() {
    if (musicPlaying) {
        menuMusic.pause();
        musicPlaying = false;
        isMuted = true;
    }
    else {
        menuMusic.play();
        musicPlaying = true;
        isMuted = false;
    }
}

bool SFMLInterface::estOuverte() const {
    return window.isOpen();
}

void SFMLInterface::zoomIn() {
    if (tailleCellule < 50) {
        tailleCellule += 2;
        celluleShape.setSize(sf::Vector2f(tailleCellule - 1, tailleCellule - 1));
    }
}

void SFMLInterface::zoomOut() {
    if (tailleCellule > 4) {
        tailleCellule -= 2;
        celluleShape.setSize(sf::Vector2f(tailleCellule - 1, tailleCellule - 1));
    }
}

void SFMLInterface::toggleCelluleAvecSouris(Grille& grille, const sf::Vector2i& mousePos) {
    if (mousePos.y >= window.getSize().y - BANDE_NOIRE_HAUTEUR) {
        return;
    }

    int colonne = mousePos.x / tailleCellule;
    int ligne = mousePos.y / tailleCellule;

    if (ligne >= 0 && ligne < grille.getNbLignes() && colonne >= 0 && colonne < grille.getNbColonnes()) {
        sauvegarderEtat(grille);
        Cellule& cellule = grille.getCellule(ligne, colonne);
        cellule.setEtat(!cellule.estVivante());
    }
}

void SFMLInterface::resetGrille(Grille& grille) {
    sauvegarderEtat(grille);
    for (int i = 0; i < grille.getNbLignes(); ++i) {
        for (int j = 0; j < grille.getNbColonnes(); ++j) {
            grille.getCellule(i, j).setEtat(false);
        }
    }
    resetMisesAJour();  // Réinitialiser le compteur lors d'un reset
}
void SFMLInterface::ajouterPattern(Grille& grille, const std::vector<std::pair<int, int>>& coords, int ligneBase, int colonneBase) {
    sauvegarderEtat(grille);
    for (const auto& coord : coords) {
        int ligne = ligneBase + coord.first;
        int colonne = colonneBase + coord.second;
        if (ligne >= 0 && ligne < grille.getNbLignes() &&
            colonne >= 0 && colonne < grille.getNbColonnes()) {
            grille.getCellule(ligne, colonne).setEtat(true);
        }
    }
}

void SFMLInterface::ajouterPlaneur(Grille& grille, int ligneBase, int colonneBase) {
    std::vector<std::pair<int, int>> planeur = {
        {0, 1}, {1, 2}, {2, 0}, {2, 1}, {2, 2}
    };
    ajouterPattern(grille, planeur, ligneBase, colonneBase);
}

void SFMLInterface::ajouterCanon(Grille& grille, int ligneBase, int colonneBase) {
    std::vector<std::pair<int, int>> canon = {
        {0, 24},
        {1, 22}, {1, 24},
        {2, 12}, {2, 13}, {2, 20}, {2, 21}, {2, 34}, {2, 35},
        {3, 11}, {3, 15}, {3, 20}, {3, 21}, {3, 34}, {3, 35},
        {4, 0}, {4, 1}, {4, 10}, {4, 16}, {4, 20}, {4, 21},
        {5, 0}, {5, 1}, {5, 10}, {5, 14}, {5, 16}, {5, 17}, {5, 22}, {5, 24},
        {6, 10}, {6, 16}, {6, 24},
        {7, 11}, {7, 15},
        {8, 12}, {8, 13}
    };
    ajouterPattern(grille, canon, ligneBase, colonneBase);
}

void SFMLInterface::ajouterOscillateur(Grille& grille, int ligneBase, int colonneBase) {
    std::vector<std::pair<int, int>> oscillateur = {
        {0, 1}, {1, 1}, {2, 1}
    };
    ajouterPattern(grille, oscillateur, ligneBase, colonneBase);
}

void SFMLInterface::sauvegarderEtat(const Grille& grille) {
    undoStack.push(captureEtatGrille(grille));
    while (!redoStack.empty()) {
        redoStack.pop();
    }
}

void SFMLInterface::undo(Grille& grille) {
    if (!undoStack.empty()) {
        redoStack.push(captureEtatGrille(grille));
        auto previousState = undoStack.top();
        undoStack.pop();
        appliquerEtatGrille(grille, previousState);
    }
}

void SFMLInterface::redo(Grille& grille) {
    if (!redoStack.empty()) {
        undoStack.push(captureEtatGrille(grille));
        auto nextState = redoStack.top();
        redoStack.pop();
        appliquerEtatGrille(grille, nextState);
    }
}

std::vector<std::vector<bool>> SFMLInterface::captureEtatGrille(const Grille& grille) {
    std::vector<std::vector<bool>> etat(grille.getNbLignes(),
        std::vector<bool>(grille.getNbColonnes()));

    for (int i = 0; i < grille.getNbLignes(); ++i) {
        for (int j = 0; j < grille.getNbColonnes(); ++j) {
            etat[i][j] = grille.getCellule(i, j).estVivante();
        }
    }
    return etat;
}

void SFMLInterface::appliquerEtatGrille(Grille& grille, const std::vector<std::vector<bool>>& etat) {
    for (int i = 0; i < grille.getNbLignes(); ++i) {
        for (int j = 0; j < grille.getNbColonnes(); ++j) {
            grille.getCellule(i, j).setEtat(etat[i][j]);
        }
    }
}
void SFMLInterface::attendreEvenements(int& vitesseSimulation, bool& enPause, Grille& grille) {
    static bool isDraggingVolume = false;
    static bool isDraggingSpeed = false;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        // Gestion du contrôle de la vitesse
        if (isDraggingSpeed || speedBar.getGlobalBounds().contains(mousePos.x, mousePos.y) ||
            speedSlider.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            isDraggingSpeed = true;
            handleSpeedControl(mousePos, vitesseSimulation);
        }
        // Gestion du contrôle du volume
        else if (isDraggingVolume || volumeBar.getGlobalBounds().contains(mousePos.x, mousePos.y) ||
            volumeSlider.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            isDraggingVolume = true;
            handleVolumeControl(mousePos);
        }
        // Gestion de la modification de la grille
        else if (!enMenu && estEnTrainDeModifier) {
            if (!zoomInSprite.getGlobalBounds().contains(mousePos.x, mousePos.y) &&
                !zoomOutSprite.getGlobalBounds().contains(mousePos.x, mousePos.y) &&
                !undoSprite.getGlobalBounds().contains(mousePos.x, mousePos.y) &&
                !redoSprite.getGlobalBounds().contains(mousePos.x, mousePos.y) &&
                !pauseSprite.getGlobalBounds().contains(mousePos.x, mousePos.y) &&
                !playSprite.getGlobalBounds().contains(mousePos.x, mousePos.y) &&
                !resetSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {

                int colonne = mousePos.x / tailleCellule;
                int ligne = mousePos.y / tailleCellule;
                sf::Vector2i celluleActuelle(colonne, ligne);

                if (celluleActuelle != derniereCelluleModifiee) {
                    toggleCelluleAvecSouris(grille, mousePos);
                    derniereCelluleModifiee = celluleActuelle;
                }
            }
        }
    }
    else {
        isDraggingSpeed = false;
        isDraggingVolume = false;
    }

    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::M) {
                toggleMusic();
            }
            if (event.key.control) {
                if (event.key.code == sf::Keyboard::Z) {
                    undo(grille);
                }
                else if (event.key.code == sf::Keyboard::Y) {
                    redo(grille);
                }
            }

            if (!enMenu) {
                switch (event.key.code) {
                case sf::Keyboard::R:
                    resetGrille(grille);
                    break;
                case sf::Keyboard::Left:
                    currentSpeed = std::max(0.0f, currentSpeed - 5.0f);
                    vitesseSimulation = 2000 - ((currentSpeed / 100.0f) * 1950);
                    updateSpeedSlider();
                    break;
                case sf::Keyboard::Right:
                    currentSpeed = std::min(100.0f, currentSpeed + 5.0f);
                    vitesseSimulation = 2000 - ((currentSpeed / 100.0f) * 1950);
                    updateSpeedSlider();
                    break;
                case sf::Keyboard::P:
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    int ligne = mousePos.y / tailleCellule;
                    int colonne = mousePos.x / tailleCellule;
                    ajouterPlaneur(grille, ligne, colonne);
                }
                break;
                case sf::Keyboard::C:
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    int ligne = mousePos.y / tailleCellule;
                    int colonne = mousePos.x / tailleCellule;
                    ajouterCanon(grille, ligne, colonne);
                }
                break;
                case sf::Keyboard::O:
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    int ligne = mousePos.y / tailleCellule;
                    int colonne = mousePos.x / tailleCellule;
                    ajouterOscillateur(grille, ligne, colonne);
                }
                break;
                case sf::Keyboard::Space:
                    enPause = !enPause;
                    break;
                case sf::Keyboard::Escape:
                    if (!enMenu) {  // Si on n'est pas déjà dans le menu
                        enMenu = true;  // Retour au menu
                        enPause = true; // Mettre le jeu en pause
                        
                    }
                    break;
                }
            }
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            if (enMenu) {
                if (boutonStart.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    enMenu = false;
                    enPause = true;
                }
                else if (boutonExit.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    window.close();
                }
            }
            else {
                if (resetSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    resetGrille(grille);
                }
                else if (zoomInSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    zoomIn();
                }
                else if (zoomOutSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    zoomOut();
                }
                else if (undoSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    undo(grille);
                }
                else if (redoSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    redo(grille);
                }
                else if (soundSprite.getGlobalBounds().contains(mousePos.x, mousePos.y) ||
                    muteSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    toggleMusic();
                }
                else if (pauseSprite.getGlobalBounds().contains(mousePos.x, mousePos.y) ||
                    playSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    enPause = !enPause;
                }
                else {
                    estEnTrainDeModifier = true;
                    derniereCelluleModifiee = sf::Vector2i(mousePos.x / tailleCellule, mousePos.y / tailleCellule);
                    toggleCelluleAvecSouris(grille, mousePos);
                }
            }
        }
        else if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                estEnTrainDeModifier = false;
                derniereCelluleModifiee = sf::Vector2i(-1, -1);
            }
        }
    }
}
