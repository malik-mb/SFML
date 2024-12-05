#include "C:/Users/Kaout/OneDrive/Documents/POO/poo/SFML/Cellule.h"
#include "C:/Users/Kaout/OneDrive/Documents/POO/poo/SFML/Grille.h"
#include <gtest/gtest.h>


TEST(GrilleTest, ProchaineIteration) {
    Grille grille(3, 3);

    // Initialisation d'un motif simple (barre horizontale)
    grille.getCellule(1, 0).definirEtatSuivant(true);
    grille.getCellule(1, 1).definirEtatSuivant(true);
    grille.getCellule(1, 2).definirEtatSuivant(true);

    // Actualisation des �tats initiaux
    for (int i = 0; i < grille.getNbLignes(); ++i) {
        for (int j = 0; j < grille.getNbColonnes(); ++j) {
            grille.getCellule(i, j).actualiserEtat();
        }
    }

    // Calculer la prochaine it�ration
    grille.calculerProchaineIteration();

    // V�rifier les r�sultats attendus
    EXPECT_TRUE(grille.getCellule(0, 1).estVivante()); // Cellule vivante
    EXPECT_TRUE(grille.getCellule(1, 1).estVivante()); // Cellule vivante
    EXPECT_TRUE(grille.getCellule(2, 1).estVivante()); // Cellule vivante

    EXPECT_FALSE(grille.getCellule(1, 0).estVivante()); // Cellule morte
    EXPECT_FALSE(grille.getCellule(1, 2).estVivante()); // Cellule morte
}
