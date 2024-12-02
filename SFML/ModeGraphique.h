#ifndef MODEGRAPHIQUE_H
#define MODEGRAPHIQUE_H

#include "ModeJeu.h"
#include "SFMLInterface.h"
#include <memory>

class ModeGraphique : public ModeJeu {
private:
    std::unique_ptr<SFMLInterface> interface;

public:
    // Constructeur prenant une r�f�rence constante pour la grille et un pointeur unique
    ModeGraphique(const Grille& grille, std::unique_ptr<SFMLInterface> interface);

    // Impl�mentation de la simulation graphique
    void lancerSimulation() override;
};

#endif // MODEGRAPHIQUE_H
