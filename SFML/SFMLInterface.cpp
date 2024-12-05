#include "SFMLInterface.h"

SFMLInterface::SFMLInterface(int largeur, int hauteur, int tailleCellule)
    : tailleCellule(tailleCellule), enPleinEcran(true) {
    // Hauteur de la bande noire � ajouter en bas de l'�cran
    const int hauteurBandeNoire = 40;

    // Cr�e une fen�tre en mode plein �cran
    window.create(sf::VideoMode::getDesktopMode(), "Simulation Graphique", sf::Style::Fullscreen);

    // R�initialise la taille de la fen�tre si n�cessaire
    largeur = window.getSize().x;
    hauteur = window.getSize().y;

    celluleShape.setSize(sf::Vector2f(tailleCellule - 1, tailleCellule - 1)); // L�g�rement plus petit

    if (!font.loadFromFile("C:\\Users\\malik\\Music\\VarelaRound-Regular.ttf")) {
        throw std::runtime_error("Erreur : Impossible de charger la police.");
    }
    // Configuration du texte
    messageTexte.setFont(font);
    messageTexte.setString("Zoom In / Zoom Out");
    messageTexte.setCharacterSize(20);
    messageTexte.setFillColor(sf::Color::White);
    messageTexte.setPosition(10, hauteur - 30);  // D�placer le texte un peu au-dessus de la bande noire

    // Configuration des boutons
    boutonZoomIn.setSize(sf::Vector2f(100, 50));  // Taille du bouton
    boutonZoomIn.setFillColor(sf::Color(100, 200, 100));  // Couleur du bouton Zoom In
    boutonZoomIn.setPosition(largeur / 2 - 150, hauteur + hauteurBandeNoire - 70);  // Position du bouton Zoom In dans la bande noire

    boutonZoomOut.setSize(sf::Vector2f(100, 50));  // Taille du bouton
    boutonZoomOut.setFillColor(sf::Color(200, 100, 100));  // Couleur du bouton Zoom Out
    boutonZoomOut.setPosition(largeur / 2 + 50, hauteur + hauteurBandeNoire - 70);  // Position du bouton Zoom Out dans la bande noire

    messageTexte.setFont(font);
    messageTexte.setString("Press Space to Pause");
    messageTexte.setCharacterSize(20); // Taille de la police
    messageTexte.setFillColor(sf::Color::White);
}

bool SFMLInterface::estOuverte() const {
    return window.isOpen();
}

void SFMLInterface::afficherGrille(const Grille& grille) {
    window.clear(sf::Color(50, 50, 50)); // Fond gris fonc�

    // Calcul de la taille de la grille (sans la bande noire)
    int hauteurGrille = window.getSize().y - 40; // La hauteur de la grille est la hauteur de la fen�tre moins la hauteur de la bande noire

    // Affichage de la grille
    for (int i = 0; i < grille.getNbLignes(); ++i) {
        for (int j = 0; j < grille.getNbColonnes(); ++j) {
            sf::VertexArray quad(sf::Quads, 4);

            // Calcul des coordonn�es de la cellule, en s'assurant que la grille ne d�passe pas la fen�tre
            float x = j * tailleCellule;
            float y = i * tailleCellule;
            float size = tailleCellule - 1;  // Un peu de marge entre les cellules

            // Choisir une couleur en fonction de l'�tat de la cellule
            if (grille.getCellule(i, j).estVivante()) {
                quad[0].color = sf::Color(0, 0, 255);     // Bleu
                quad[1].color = sf::Color(0, 0, 200);     // Bleu sombre
                quad[2].color = sf::Color(148, 0, 211);  // Violet
                quad[3].color = sf::Color(186, 85, 211); // Violet clair
            }
            else {
                quad[0].color = sf::Color(169, 169, 169); // Gris clair
                quad[1].color = sf::Color(169, 169, 169); // Gris clair
                quad[2].color = sf::Color(105, 105, 105); // Gris sombre
                quad[3].color = sf::Color(105, 105, 105); // Gris sombre
            }

            // D�finir les positions des coins du quadrilat�re
            quad[0].position = sf::Vector2f(x, y);
            quad[1].position = sf::Vector2f(x + size, y);
            quad[2].position = sf::Vector2f(x + size, y + size);
            quad[3].position = sf::Vector2f(x, y + size);

            window.draw(quad);
        }
    }

    // Bande noire en bas de l'�cran (ne fait pas partie de la grille)
    sf::RectangleShape bandeNoire(sf::Vector2f(window.getSize().x, 40));
    bandeNoire.setPosition(0, window.getSize().y - 40); // Placer la bande noire en bas
    bandeNoire.setFillColor(sf::Color::Black);
    window.draw(bandeNoire);

    // Affichage du texte "Press Space to Pause"
    messageTexte.setPosition(
        (window.getSize().x - messageTexte.getLocalBounds().width) / 2,
        window.getSize().y - 30  // Placer le texte � 10px au-dessus de la bande noire
    );
    window.draw(messageTexte);

    // Affichage des boutons dans la bande noire
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

        // G�rer les �v�nements de touches
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Right) {
                vitesseSimulation = std::max(vitesseSimulation - 200, 100);
            }
            if (event.key.code == sf::Keyboard::Left) {
                vitesseSimulation = std::min(vitesseSimulation + 200, 2000);
            }
            if (event.key.code == sf::Keyboard::Space) {
                enPause = !enPause; // Alterne l'�tat de pause
            }
            // Quitter le mode plein �cran avec �chap
            if (event.key.code == sf::Keyboard::Escape) {
                if (enPleinEcran) {
                    window.create(sf::VideoMode(800, 600), "Simulation Graphique", sf::Style::Close); // Cr�e une fen�tre fen�tr�e
                    enPleinEcran = false; // Passer en mode fen�tr�
                }
                else {
                    window.create(sf::VideoMode::getDesktopMode(), "Simulation Graphique", sf::Style::Fullscreen); // Repasser en plein �cran
                    enPleinEcran = true; // Retour en mode plein �cran
                }
            }
        }
    }
}
