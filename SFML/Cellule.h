#ifndef CELLULE_H
#define CELLULE_H

class Cellule {
private:
    bool etatActuel;
    bool etatSuivant;

public:
    Cellule(bool etat = false);

    bool estVivante() const;
    void definirEtatSuivant(bool etat);
    void actualiserEtat();
};

#endif // CELLULE_H