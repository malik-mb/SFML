#ifndef JEUDESLAVIE_H
#define JEUDESLAVIE_H

#include "Grille.h"
#include "ModeJeu.h"

class JeuDeLaVie {
private:
    ModeJeu* modeJeu;
    Grille grille;

public:
    JeuDeLaVie(ModeJeu* modeJeu, Grille grille);
    void demarrerJeu();
};

#endif // JEUDESLAVIE_H
