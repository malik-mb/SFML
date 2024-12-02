#include "Cellule.h"

Cellule::Cellule(bool etat) : etatActuel(etat), etatSuivant(false) {}

bool Cellule::estVivante() const {
    return etatActuel;
}

void Cellule::definirEtatSuivant(bool etat) {
    etatSuivant = etat;
}

void Cellule::actualiserEtat() {
    etatActuel = etatSuivant;
}