#ifndef MODEJEU_H
#define MODEJEU_H

#include "Grille.h"

class ModeJeu {
protected:
    Grille grille;

public:
    ModeJeu(const Grille& grille); // Constructeur prenant une référence constante
    virtual ~ModeJeu() = default;
    virtual void lancerSimulation() = 0; // Méthode virtuelle pure
};

#endif // MODEJEU_H
