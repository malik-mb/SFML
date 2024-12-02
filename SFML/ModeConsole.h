#ifndef MODECONSOLE_H
#define MODECONSOLE_H

#include "ModeJeu.h"
#include "GestionFichier.h"

class ModeConsole : public ModeJeu {
public:
    // Constructeur
    ModeConsole(Grille grille);

    // Lancer la simulation en mode console
    void lancerSimulation() override;
};

#endif // MODECONSOLE_H
