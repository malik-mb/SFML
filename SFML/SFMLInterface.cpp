#include "SFMLInterface.h"
#include <stdexcept>
#include <iostream>

SFMLInterface::SFMLInterface(int largeur, int hauteur, int tailleCellule)
    : tailleCellule(tailleCellule), enPleinEcran(true), enMenu(true), musicPlaying(false),
    estEnTrainDeModifier(false), derniereCelluleModifiee(-1, -1) {

    // Cr�ation de la fen�tre en plein �cran
    window.create(sf::VideoMode::getDesktopMode(), "Jeu de la Vie", sf::Style::Fullscreen);

    // Configuration de la forme des cellules
    celluleShape.setSize(sf::Vector2f(tailleCellule - 1, tailleCellule - 1));

    // Chargement de la police
    if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        std::cerr << "Erreur : Impossible de charger la police." << std::endl;
    }

    // Chargement des textures de zoom
    if (!zoomInTexture.loadFromFile("C:\\Users\\malik\\Music\\icons8-zoomer-48.png")) {
        std::cerr << "Erreur : Impossible de charger l'ic�ne de zoom in" << std::endl;
    }
    if (!zoomOutTexture.loadFromFile("C:\\Users\\malik\\Music\\icons8-d�zoomer-48.png")) {
        std::cerr << "Erreur : Impossible de charger l'ic�ne de zoom out" << std::endl;
    }

    // Configuration des sprites de zoom
    zoomInSprite.setTexture(zoomInTexture);
    zoomOutSprite.setTexture(zoomOutTexture);

    // Positionnement des ic�nes de zoom en bas � droite
    float spacing = 20.0f;
    zoomOutSprite.setPosition(
        window.getSize().x - zoomOutSprite.getGlobalBounds().width - spacing,
        window.getSize().y - BANDE_NOIRE_HAUTEUR / 2 - zoomOutSprite.getGlobalBounds().height / 2
    );
    zoomInSprite.setPosition(
        zoomOutSprite.getPosition().x - zoomInSprite.getGlobalBounds().width - spacing,
        window.getSize().y - BANDE_NOIRE_HAUTEUR / 2 - zoomInSprite.getGlobalBounds().height / 2
    );

    // Configuration de la musique - Gestion plus souple des erreurs
    bool musiqueChargee = false;
    try {
        if (menuMusic.openFromFile("C:\\Users\\malik\\Downloads\\PNL-Onizuka-_Instrumental_-Instrumentals.ogg")) {
            menuMusic.setLoop(true);
            menuMusic.setVolume(50.0f);
            menuMusic.play();
            musicPlaying = true;
            musiqueChargee = true;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Erreur lors du chargement de la musique : " << e.what() << std::endl;
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

    // Configuration des boutons
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
    // Configuration des textes des boutons
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

    // Configuration du message
    messageTexte.setFont(font);
    messageTexte.setString("Cliquez ou maintenez pour modifier les cellules");
    messageTexte.setCharacterSize(20);
    messageTexte.setFillColor(sf::Color::White);
    messageTexte.setPosition(
        (window.getSize().x - messageTexte.getLocalBounds().width) / 2,
        window.getSize().y - BANDE_NOIRE_HAUTEUR / 2 - messageTexte.getLocalBounds().height / 2
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

void SFMLInterface::toggleCelluleAvecSouris(Grille& grille, const sf::Vector2i& mousePos) {
    // V�rifier si le clic est dans la zone de la grille (pas dans la bande noire)
    if (mousePos.y >= window.getSize().y - BANDE_NOIRE_HAUTEUR) {
        return;
    }

    int colonne = mousePos.x / tailleCellule;
    int ligne = mousePos.y / tailleCellule;

    if (ligne >= 0 && ligne < grille.getNbLignes() && colonne >= 0 && colonne < grille.getNbColonnes()) {
        Cellule& cellule = grille.getCellule(ligne, colonne);
        cellule.setEtat(!cellule.estVivante());
    }
}

bool SFMLInterface::estOuverte() const {
    return window.isOpen();
}

void SFMLInterface::afficherMenu() {
    window.clear(sf::Color(30, 30, 30));

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

    // Calculer la zone d'affichage de la grille (sans la bande noire)
    int hauteurGrille = window.getSize().y - BANDE_NOIRE_HAUTEUR;

    for (int i = 0; i < grille.getNbLignes(); ++i) {
        for (int j = 0; j < grille.getNbColonnes(); ++j) {
            // Ne dessiner que si la cellule est au-dessus de la bande noire
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

    // Dessiner la bande noire
    sf::RectangleShape bandeNoire(sf::Vector2f(static_cast<float>(window.getSize().x), BANDE_NOIRE_HAUTEUR));
    bandeNoire.setPosition(0, static_cast<float>(window.getSize().y - BANDE_NOIRE_HAUTEUR));
    bandeNoire.setFillColor(sf::Color::Black);
    window.draw(bandeNoire);

    // Dessiner le message
    messageTexte.setPosition(
        (window.getSize().x - messageTexte.getLocalBounds().width) / 2,
        window.getSize().y - BANDE_NOIRE_HAUTEUR / 2 - messageTexte.getLocalBounds().height / 2
    );
    window.draw(messageTexte);

    // Dessiner les ic�nes de zoom
    window.draw(zoomInSprite);
    window.draw(zoomOutSprite);

    window.display();
}

void SFMLInterface::attendreEvenements(int& vitesseSimulation, bool& enPause, Grille& grille) {
    // Gestion du clic maintenu
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !enMenu && estEnTrainDeModifier) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        // V�rifier si on est sur les boutons de zoom
        if (!zoomInSprite.getGlobalBounds().contains(mousePos.x, mousePos.y) &&
            !zoomOutSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {

            int colonne = mousePos.x / tailleCellule;
            int ligne = mousePos.y / tailleCellule;
            sf::Vector2i celluleActuelle(colonne, ligne);

            // Si on est sur une nouvelle cellule
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

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::M) {
            toggleMusic();
        }

        if (enMenu) {
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (boutonStart.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    enMenu = false;
                    enPause = true;  // D�marrer en pause
                    menuMusic.stop();
                    messageTexte.setString("PAUSE - Appuyez sur ESPACE pour d�marrer");
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

        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            if (zoomInSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                zoomIn();
            }
            else if (zoomOutSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                zoomOut();
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
                if (enPause) {
                    messageTexte.setString("PAUSE - Le jeu est en pause");
                }
                else {
                    messageTexte.setString("Cliquez ou maintenez pour modifier les cellules");
                }
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