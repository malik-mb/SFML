#include "SFMLInterface.h"
#include <stdexcept>
#include <iostream>

SFMLInterface::SFMLInterface(int largeur, int hauteur, int tailleCellule)
    : tailleCellule(tailleCellule), enPleinEcran(true), enMenu(true) {

    // Création de la fenêtre en plein écran
    window.create(sf::VideoMode::getDesktopMode(), "Jeu de la Vie", sf::Style::Fullscreen);

    // Configuration de la forme des cellules
    celluleShape.setSize(sf::Vector2f(tailleCellule - 1, tailleCellule - 1));

    // Chargement de la police
    if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        throw std::runtime_error("Erreur : Impossible de charger la police.");
    }

    // Configuration du titre
    titreTexte.setFont(font);
    titreTexte.setString("Jeu de la Vie");
    titreTexte.setCharacterSize(50);
    titreTexte.setFillColor(sf::Color::White);
    titreTexte.setPosition(
        (window.getSize().x - titreTexte.getLocalBounds().width) / 2,
        window.getSize().y / 4
    );

    // Configuration du bouton Start
    boutonStart.setSize(sf::Vector2f(200, 60));
    boutonStart.setFillColor(sf::Color(50, 150, 50));
    boutonStart.setPosition(
        (window.getSize().x - 200) / 2,
        (window.getSize().y - 60) / 2
    );

    // Configuration du texte Start
    startTexte.setFont(font);
    startTexte.setString("START");
    startTexte.setCharacterSize(30);
    startTexte.setFillColor(sf::Color::White);
    startTexte.setPosition(
        (window.getSize().x - startTexte.getLocalBounds().width) / 2,
        (window.getSize().y - startTexte.getLocalBounds().height) / 2
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

bool SFMLInterface::estOuverte() const {
    return window.isOpen();
}

void SFMLInterface::afficherMenu() {
    window.clear(sf::Color(30, 30, 30));

    // Dessiner le titre
    window.draw(titreTexte);

    // Effet de survol pour le bouton Start
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (boutonStart.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        boutonStart.setFillColor(sf::Color(70, 170, 70));
    }
    else {
        boutonStart.setFillColor(sf::Color(50, 150, 50));
    }

    window.draw(boutonStart);
    window.draw(startTexte);
    window.display();
}

void SFMLInterface::afficherGrille(const Grille& grille) {
    window.clear(sf::Color(50, 50, 50)); // Fond gris foncé

    // Calcul de la taille de la grille (sans la bande noire)
    int hauteurGrille = window.getSize().y - 40;

    // Affichage de la grille
    for (int i = 0; i < grille.getNbLignes(); ++i) {
        for (int j = 0; j < grille.getNbColonnes(); ++j) {
            sf::VertexArray quad(sf::Quads, 4);

            float x = j * tailleCellule;
            float y = i * tailleCellule;
            float size = tailleCellule - 1;

            // Choisir une couleur en fonction de l'état de la cellule
            if (grille.getCellule(i, j).estVivante()) {
                quad[0].color = sf::Color(0, 0, 255);     // Bleu
                quad[1].color = sf::Color(0, 0, 200);     // Bleu sombre
                quad[2].color = sf::Color(148, 0, 211);   // Violet
                quad[3].color = sf::Color(186, 85, 211);  // Violet clair
            }
            else {
                quad[0].color = sf::Color(169, 169, 169); // Gris clair
                quad[1].color = sf::Color(169, 169, 169); // Gris clair
                quad[2].color = sf::Color(105, 105, 105); // Gris sombre
                quad[3].color = sf::Color(105, 105, 105); // Gris sombre
            }

            // Définir les positions des coins du quadrilatère
            quad[0].position = sf::Vector2f(x, y);
            quad[1].position = sf::Vector2f(x + size, y);
            quad[2].position = sf::Vector2f(x + size, y + size);
            quad[3].position = sf::Vector2f(x, y + size);

            window.draw(quad);
        }
    }

    // Bande noire en bas de l'écran
    sf::RectangleShape bandeNoire(sf::Vector2f(window.getSize().x, 40));
    bandeNoire.setPosition(0, window.getSize().y - 40);
    bandeNoire.setFillColor(sf::Color::Black);
    window.draw(bandeNoire);

    // Affichage du texte "Press Space to Pause"
    messageTexte.setPosition(
        (window.getSize().x - messageTexte.getLocalBounds().width) / 2,
        window.getSize().y - 30
    );
    window.draw(messageTexte);

    // Affichage des boutons de zoom
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

        // Gestion du menu
        if (enMenu) {
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::FloatRect startBounds = boutonStart.getGlobalBounds();

                if (startBounds.contains(mousePos.x, mousePos.y)) {
                    enMenu = false;
                    enPause = false;
                }
            }
            continue;
        }

        // Gestion des touches
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

        // Gestion des clics de souris pour le zoom
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
    if (tailleCellule < 50) {  // Limite maximale de zoom
        tailleCellule += 2;
        celluleShape.setSize(sf::Vector2f(tailleCellule - 1, tailleCellule - 1));
    }
}

void SFMLInterface::zoomOut() {
    if (tailleCellule > 4) {  // Limite minimale de zoom
        tailleCellule -= 2;
        celluleShape.setSize(sf::Vector2f(tailleCellule - 1, tailleCellule - 1));
    }
}

bool SFMLInterface::chargerPolice(const std::string& cheminFichier) {
    return font.loadFromFile(cheminFichier);
}