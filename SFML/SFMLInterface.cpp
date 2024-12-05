#include "SFMLInterface.h"
#include <stdexcept>
#include <iostream>

SFMLInterface::SFMLInterface(int largeur, int hauteur, int tailleCellule)
    : tailleCellule(tailleCellule), enPleinEcran(true), enMenu(true), musicPlaying(true) {

    // Création de la fenêtre en plein écran
    window.create(sf::VideoMode::getDesktopMode(), "Jeu de la Vie", sf::Style::Fullscreen);

    // Configuration de la forme des cellules
    celluleShape.setSize(sf::Vector2f(tailleCellule - 1, tailleCellule - 1));

    // Chargement de la police
    if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        throw std::runtime_error("Erreur : Impossible de charger la police.");
    }

    // Configuration de la musique
    if (!menuMusic.openFromFile("C:\\Users\\malik\\Downloads\\PNL-Onizuka-_Instrumental_-Instrumentals.ogg")) {
        throw std::runtime_error("Erreur : Impossible de charger la musique.");
    }
    menuMusic.setLoop(true);
    menuMusic.setVolume(50.0f);
    menuMusic.play();

    // Configuration du titre
    titreTexte.setFont(font);
    titreTexte.setString("Jeu de la Vie");
    titreTexte.setCharacterSize(50);
    titreTexte.setFillColor(sf::Color::White);
    titreTexte.setPosition(
        (window.getSize().x - titreTexte.getLocalBounds().width) / 2,
        window.getSize().y / 4
    );

    // Configuration du texte de musique
    musicTexte.setFont(font);
    musicTexte.setString("Appuyez sur M pour activer/desactiver la musique");
    musicTexte.setCharacterSize(20);
    musicTexte.setFillColor(sf::Color::White);
    musicTexte.setPosition(10, window.getSize().y - 30);

    // Configuration commune pour tous les boutons
    const float boutonLargeur = 200;
    const float boutonHauteur = 60;
    const float espacementBoutons = 20;
    const float centreX = window.getSize().x / 2;
    const float premierBoutonY = window.getSize().y / 2;

    // Configuration du bouton Start
    boutonStart.setSize(sf::Vector2f(boutonLargeur, boutonHauteur));
    boutonStart.setFillColor(sf::Color(50, 150, 50));
    boutonStart.setPosition(centreX - boutonLargeur / 2, premierBoutonY);
    startTexte.setFont(font);
    startTexte.setString("START");
    startTexte.setCharacterSize(30);
    startTexte.setFillColor(sf::Color::White);
    startTexte.setPosition(
        centreX - startTexte.getLocalBounds().width / 2,
        premierBoutonY + (boutonHauteur - startTexte.getLocalBounds().height) / 2
    );

    // Configuration du bouton Paramètres
    boutonParams.setSize(sf::Vector2f(boutonLargeur, boutonHauteur));
    boutonParams.setFillColor(sf::Color(50, 150, 50));
    boutonParams.setPosition(centreX - boutonLargeur / 2, premierBoutonY + boutonHauteur + espacementBoutons);
    paramsTexte.setFont(font);
    paramsTexte.setString("PARAMETRES");
    paramsTexte.setCharacterSize(30);
    paramsTexte.setFillColor(sf::Color::White);
    paramsTexte.setPosition(
        centreX - paramsTexte.getLocalBounds().width / 2,
        premierBoutonY + boutonHauteur + espacementBoutons + (boutonHauteur - paramsTexte.getLocalBounds().height) / 2
    );

    // Configuration du bouton Tutorial
    boutonTutorial.setSize(sf::Vector2f(boutonLargeur, boutonHauteur));
    boutonTutorial.setFillColor(sf::Color(50, 150, 50));
    boutonTutorial.setPosition(centreX - boutonLargeur / 2, premierBoutonY + (boutonHauteur + espacementBoutons) * 2);
    tutorialTexte.setFont(font);
    tutorialTexte.setString("TUTORIAL");
    tutorialTexte.setCharacterSize(30);
    tutorialTexte.setFillColor(sf::Color::White);
    tutorialTexte.setPosition(
        centreX - tutorialTexte.getLocalBounds().width / 2,
        premierBoutonY + (boutonHauteur + espacementBoutons) * 2 + (boutonHauteur - tutorialTexte.getLocalBounds().height) / 2
    );

    // Configuration du bouton Exit
    boutonExit.setSize(sf::Vector2f(boutonLargeur, boutonHauteur));
    boutonExit.setFillColor(sf::Color(50, 150, 50));
    boutonExit.setPosition(centreX - boutonLargeur / 2, premierBoutonY + (boutonHauteur + espacementBoutons) * 3);
    exitTexte.setFont(font);
    exitTexte.setString("EXIT");
    exitTexte.setCharacterSize(30);
    exitTexte.setFillColor(sf::Color::White);
    exitTexte.setPosition(
        centreX - exitTexte.getLocalBounds().width / 2,
        premierBoutonY + (boutonHauteur + espacementBoutons) * 3 + (boutonHauteur - exitTexte.getLocalBounds().height) / 2
    );

    // Configuration des boutons de zoom
    boutonZoomIn.setSize(sf::Vector2f(100, 50));
    boutonZoomIn.setFillColor(sf::Color(100, 200, 100));
    boutonZoomIn.setPosition(window.getSize().x / 2 - 150, window.getSize().y - 70);

    boutonZoomOut.setSize(sf::Vector2f(100, 50));
    boutonZoomOut.setFillColor(sf::Color(200, 100, 100));
    boutonZoomOut.setPosition(window.getSize().x / 2 + 50, window.getSize().y - 70);

    // Configuration du message
    messageTexte.setFont(font);
    messageTexte.setString("Press Space to Pause");
    messageTexte.setCharacterSize(20);
    messageTexte.setFillColor(sf::Color::White);
    messageTexte.setPosition(10, window.getSize().y - 30);
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

bool SFMLInterface::estOuverte() const {
    return window.isOpen();
}

void SFMLInterface::afficherMenu() {
    window.clear(sf::Color(30, 30, 30));

    // Dessiner le titre
    window.draw(titreTexte);

    // Effet de survol pour les boutons
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

void SFMLInterface::afficherGrille(const Grille& grille) {
    window.clear(sf::Color(50, 50, 50));

    for (int i = 0; i < grille.getNbLignes(); ++i) {
        for (int j = 0; j < grille.getNbColonnes(); ++j) {
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

    sf::RectangleShape bandeNoire(sf::Vector2f(static_cast<float>(window.getSize().x), 40.0f));
    bandeNoire.setPosition(0, static_cast<float>(window.getSize().y - 40));
    bandeNoire.setFillColor(sf::Color::Black);
    window.draw(bandeNoire);

    messageTexte.setPosition(
        (window.getSize().x - messageTexte.getLocalBounds().width) / 2,
        window.getSize().y - 30
    );
    window.draw(messageTexte);

    window.draw(boutonZoomIn);
    window.draw(boutonZoomOut);

    window.display();
}

void SFMLInterface::attendreEvenements(int& vitesseSimulation, bool& enPause) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        // Gestion de la musique
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::M) {
            toggleMusic();
        }

        if (enMenu) {
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (boutonStart.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    enMenu = false;
                    enPause = false;
                    menuMusic.stop();
                }
                else if (boutonParams.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    messageTexte.setString("Les parametres seront bientot disponibles!");
                }
                else if (boutonTutorial.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    messageTexte.setString("Le tutorial arrive prochainement!");
                }
                else if (boutonExit.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    window.close();
                }
            }
            continue;
        }

        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
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
            default:
                break;
            }
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            if (boutonZoomIn.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                zoomIn();
            }
            else if (boutonZoomOut.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                zoomOut();
            }
        }
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

bool SFMLInterface::chargerPolice(const std::string& cheminFichier) {
    return font.loadFromFile(cheminFichier);
}