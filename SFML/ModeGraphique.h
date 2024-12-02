#ifndef MODEGRAPHIQUE_H
#define MODEGRAPHIQUE_H

#include "ModeJeu.h"
#include "SFMLInterface.h"
#include <memory>

class ModeGraphique : public ModeJeu {
private:
    std::unique_ptr<SFMLInterface> interface;

public:
    // Constructeur prenant une référence constante pour la grille et un pointeur unique
    ModeGraphique(const Grille& grille, std::unique_ptr<SFMLInterface> interface);

    // Implémentation de la simulation graphique
    void lancerSimulation() override;
};

#endif // MODEGRAPHIQUE_H
