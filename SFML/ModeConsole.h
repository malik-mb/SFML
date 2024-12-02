
#ifndef MODECONSOLE_H
#define MODECONSOLE_H

#include "ModeJeu.h"

class ModeConsole : public ModeJeu {
public:

    ModeConsole(Grille grille);


    void lancerSimulation() override;
};

#endif

