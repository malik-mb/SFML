#include "SFMLInterface.h"

SFMLInterface::SFMLInterface(int largeur, int hauteur, int tailleCellule)
    : tailleCellule(tailleCellule) {
    window.create(sf::VideoMode(largeur, hauteur), "Simulation Graphique");
    celluleShape.setSize(sf::Vector2f(tailleCellule - 1, tailleCellule - 1)); // L�g�rement plus petit pour un effet de grille
}

bool SFMLInterface::estOuverte() const {
    return window.isOpen();
}
void SFMLInterface::afficherGrille(const Grille& grille) {
    window.clear(sf::Color(50, 50, 50)); // Fond gris fonc�

    for (int i = 0; i < grille.getNbLignes(); ++i) {
        for (int j = 0; j < grille.getNbColonnes(); ++j) {
            // Cr�er un VertexArray pour chaque cellule
            sf::VertexArray quad(sf::Quads, 4);

            // D�finir les coins du quadrilat�re (cellule)
            float x = j * tailleCellule;
            float y = i * tailleCellule;
            float size = tailleCellule - 1;  // Un peu de marge entre les cellules

            // Choisir un d�grad� bas� sur la vivacit� de la cellule (juste un exemple ici)
            if (grille.getCellule(i, j).estVivante()) {
                // Bleu � Violet
                quad[0].color = sf::Color(0, 0, 255); // Bleu
                quad[1].color = sf::Color(0, 0, 200); // Bleu sombre
                quad[2].color = sf::Color(148, 0, 211); // Violet
                quad[3].color = sf::Color(186, 85, 211); // Violet clair
            } else {
                // Gris clair � gris fonc� pour les cellules mortes
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

            // Dessiner le quadrilat�re (cellule) sur la fen�tre
            window.draw(quad);
        }
    }

    window.display();
}

void SFMLInterface::attendreEvenements(int& vitesseSimulation) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        // G�rer les �v�nements de touches pour ajuster la vitesse
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Right) {
                // R�duire la vitesse de simulation
                vitesseSimulation = std::max(vitesseSimulation - 200, 100);
            }
            if (event.key.code == sf::Keyboard::Left) {
                // Augmenter la vitesse de simulation
                vitesseSimulation = std::min(vitesseSimulation + 200, 2000);
            }
        }
    }
}


