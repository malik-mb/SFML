#ifndef MODEGRAPHIQUE_H
#define MODEGRAPHIQUE_H

#include "ModeJeu.h"
#include "SFMLInterface.h"
#include <memory>

class ModeGraphique : public ModeJeu {
private:
    std::unique_ptr<SFMLInterface> interface;
    bool enPause;

public:
    ModeGraphique(const Grille& grille, std::unique_ptr<SFMLInterface> interface);
    virtual void lancerSimulation() override;
};

#endif // MODEGRAPHIQUE_H