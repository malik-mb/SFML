#include "ModeConsole.h"
#include <iostream>
#include <thread>
#include <chrono>

// Constructeur
ModeConsole::ModeConsole(Grille grille) : ModeJeu(grille) {}

// Implémentation de la simulation en mode console
void ModeConsole::lancerSimulation() {
    while (true) {
        grille.afficherEtat();
        grille.calculerProchaineIteration();
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Pause de 500 ms
    }
}