#include "JeuDeLaVie.h"

JeuDeLaVie::JeuDeLaVie(ModeJeu* mode, Grille grille)
    : modeJeu(mode), grille(grille) {
}

void JeuDeLaVie::demarrerJeu() {
    modeJeu->lancerSimulation();
}
