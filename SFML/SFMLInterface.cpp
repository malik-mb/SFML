#include "SFMLInterface.h"
#include <stdexcept>
#include <iostream>

SFMLInterface::SFMLInterface(int largeur, int hauteur, int tailleCellule)
    : tailleCellule(tailleCellule), enPleinEcran(true), enMenu(true), musicPlaying(false),
    estEnTrainDeModifier(false), derniereCelluleModifiee(-1, -1) {

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

    // Configuration des sprites
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

    // Redimensionnement des sprites de pattern
    float patternSize = 40.0f;
    float scale;

    scale = patternSize / oscillateurSprite.getGlobalBounds().width;
    oscillateurSprite.setScale(scale, scale);
    scale = patternSize / planeurSprite.getGlobalBounds().width;
    planeurSprite.setScale(scale, scale);
    scale = patternSize / canonSprite.getGlobalBounds().width;
    canonSprite.setScale(scale, scale);

    float spacing = 20.0f;

    // Positionnement des sprites
    resetSprite.setPosition(
        spacing,
        window.getSize().y - BANDE_NOIRE_HAUTEUR / 2 - resetSprite.getGlobalBounds().height / 2
    );

    // Position des patterns dans la bande noire
    float startX = resetSprite.getPosition().x + resetSprite.getGlobalBounds().width + 20.0f;
    float patternY = window.getSize().y - BANDE_NOIRE_HAUTEUR / 2 - patternSize / 2;
    float spacingPatterns = 120.0f;

    oscillateurSprite.setPosition(startX, patternY);
    planeurSprite.setPosition(startX + spacingPatterns, patternY);
    canonSprite.setPosition(startX + spacingPatterns * 2, patternY);
    // Configuration des textes des patterns
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

    zoomOutSprite.setPosition(
        window.getSize().x - zoomOutSprite.getGlobalBounds().width - spacing,
        window.getSize().y - BANDE_NOIRE_HAUTEUR / 2 - zoomOutSprite.getGlobalBounds().height / 2
    );
    zoomInSprite.setPosition(
        zoomOutSprite.getPosition().x - zoomInSprite.getGlobalBounds().width - spacing,
        window.getSize().y - BANDE_NOIRE_HAUTEUR / 2 - zoomInSprite.getGlobalBounds().height / 2
    );

    float messageX = window.getSize().x / 2;
    float messageY = window.getSize().y - BANDE_NOIRE_HAUTEUR / 2;

    undoSprite.setPosition(
        messageX - undoSprite.getGlobalBounds().width - spacing * 2,
        messageY - undoSprite.getGlobalBounds().height / 2
    );

    pauseSprite.setPosition(
        messageX - pauseSprite.getGlobalBounds().width / 2,
        messageY - pauseSprite.getGlobalBounds().height / 2
    );
    playSprite.setPosition(
        messageX - playSprite.getGlobalBounds().width / 2,
        messageY - playSprite.getGlobalBounds().height / 2
    );

    redoSprite.setPosition(
        messageX + spacing * 2,
        messageY - redoSprite.getGlobalBounds().height / 2
    );

    messageTexte.setFont(font);
    messageTexte.setString("");
    messageTexte.setCharacterSize(20);
    messageTexte.setFillColor(sf::Color::White);

    // Configuration de la musique
    try {
        if (menuMusic.openFromFile("C:\\Users\\malik\\Downloads\\PNL-Onizuka-_Instrumental_-Instrumentals.ogg")) {
            menuMusic.setLoop(true);
            menuMusic.setVolume(50.0f);
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
    musicTexte.setFont(font);
    musicTexte.setString("Appuyez sur M pour activer/desactiver la musique");
    musicTexte.setCharacterSize(20);
    musicTexte.setFillColor(sf::Color::White);
    musicTexte.setPosition(10, window.getSize().y - 30);

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

void SFMLInterface::toggleMusic() {
    if (musicPlaying) {
        menuMusic.pause();
        musicPlaying = false;
    }
    else {
        menuMusic.play();
        musicPlaying = true;
    }
}

void SFMLInterface::resetGrille(Grille& grille) {
    sauvegarderEtat(grille);
    for (int i = 0; i < grille.getNbLignes(); ++i) {
        for (int j = 0; j < grille.getNbColonnes(); ++j) {
            grille.getCellule(i, j).setEtat(false);
        }
    }
}
void SFMLInterface::sauvegarderEtat(const Grille& grille) {
    undoStack.push(captureEtatGrille(grille));
    while (!redoStack.empty()) {
        redoStack.pop();
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

void SFMLInterface::afficherGrille(const Grille& grille, bool enPause) {
    window.clear(sf::Color(50, 50, 50));

    int hauteurGrille = window.getSize().y - BANDE_NOIRE_HAUTEUR;

    for (int i = 0; i < grille.getNbLignes(); ++i) {
        for (int j = 0; j < grille.getNbColonnes(); ++j) {
            if (i * tailleCellule < hauteurGrille) {
                sf::VertexArray quad(sf::Quads, 4);
                float x = static_cast<float>(j * tailleCellule);
                float y = static_cast<float>(i * tailleCellule);
                float size = static_cast<float>(tailleCellule - 1);

                if (grille.getCellule(i, j).estVivante()) {
                    quad[0].color = sf::Color(0, 0, 255);
                    quad[1].color = sf::Color(0, 0, 200);
                    quad[2].color = sf::Color(148, 0, 211);
                    quad[3].color = sf::Color(186, 85, 211);
                }
                else {
                    quad[0].color = sf::Color(169, 169, 169);
                    quad[1].color = sf::Color(169, 169, 169);
                    quad[2].color = sf::Color(105, 105, 105);
                    quad[3].color = sf::Color(105, 105, 105);
                }

                quad[0].position = sf::Vector2f(x, y);
                quad[1].position = sf::Vector2f(x + size, y);
                quad[2].position = sf::Vector2f(x + size, y + size);
                quad[3].position = sf::Vector2f(x, y + size);

                window.draw(quad);
            }
        }
    }

    sf::RectangleShape bandeNoire(sf::Vector2f(static_cast<float>(window.getSize().x), BANDE_NOIRE_HAUTEUR));
    bandeNoire.setPosition(0, static_cast<float>(window.getSize().y - BANDE_NOIRE_HAUTEUR));
    bandeNoire.setFillColor(sf::Color::Black);
    window.draw(bandeNoire);

    // Dessiner tous les sprites et textes
    window.draw(resetSprite);
    window.draw(zoomInSprite);
    window.draw(zoomOutSprite);
    window.draw(undoSprite);
    window.draw(redoSprite);

    // Dessiner les patterns et leurs textes
    window.draw(oscillateurSprite);
    window.draw(planeurSprite);
    window.draw(canonSprite);
    window.draw(oscillateurTexte);
    window.draw(planeurTexte);
    window.draw(canonTexte);

    if (enPause) {
        window.draw(playSprite);
    }
    else {
        window.draw(pauseSprite);
    }

    window.display();
}
void SFMLInterface::attendreEvenements(int& vitesseSimulation, bool& enPause, Grille& grille) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !enMenu && estEnTrainDeModifier) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

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
                case sf::Keyboard::P:  // Planeur
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    int ligne = mousePos.y / tailleCellule;
                    int colonne = mousePos.x / tailleCellule;
                    ajouterPlaneur(grille, ligne, colonne);
                }
                break;
                case sf::Keyboard::C:  // Canon
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    int ligne = mousePos.y / tailleCellule;
                    int colonne = mousePos.x / tailleCellule;
                    ajouterCanon(grille, ligne, colonne);
                }
                break;
                case sf::Keyboard::O:  // Oscillateur
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    int ligne = mousePos.y / tailleCellule;
                    int colonne = mousePos.x / tailleCellule;
                    ajouterOscillateur(grille, ligne, colonne);
                }
                break;
                case sf::Keyboard::R:  // Reset
                    resetGrille(grille);
                    break;
                case sf::Keyboard::Right:
                    vitesseSimulation = std::max(vitesseSimulation - 200, 100);
                    break;
                case sf::Keyboard::Left:
                    vitesseSimulation = std::min(vitesseSimulation + 200, 2000);
                    break;
                case sf::Keyboard::Space:
                    enPause = !enPause;
                    break;
                case sf::Keyboard::Escape:
                    if (enPleinEcran) {
                        window.create(sf::VideoMode(800, 600), "Jeu de la Vie", sf::Style::Close);
                        enPleinEcran = false;
                    }
                    else {
                        window.create(sf::VideoMode::getDesktopMode(), "Jeu de la Vie", sf::Style::Fullscreen);
                        enPleinEcran = true;
                    }
                    break;
                }
            }
        }

        if (enMenu) {
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (boutonStart.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    enMenu = false;
                    enPause = true;
                    menuMusic.stop();
                    messageTexte.setString("");
                }
                else if (boutonParams.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    messageTexte.setString("");
                }
                else if (boutonTutorial.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    messageTexte.setString("");
                }
                else if (boutonExit.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    window.close();
                }
            }
            continue;
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

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
        else if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                estEnTrainDeModifier = false;
                derniereCelluleModifiee = sf::Vector2i(-1, -1);
            }
        }
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

bool SFMLInterface::estOuverte() const {
    return window.isOpen();
}

bool SFMLInterface::chargerPolice(const std::string& cheminFichier) {
    return font.loadFromFile(cheminFichier);
}