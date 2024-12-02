#include "GestionFichier.h"
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <cstdlib> // Pour system()

void creerDossier(const std::string& dossier) {
    struct stat info;
    if (stat(dossier.c_str(), &info) != 0) {
        std::string commande = "mkdir -p " + dossier;
        if (system(commande.c_str()) != 0) {
            std::cerr << "Erreur lors de la création du dossier : " << dossier << std::endl;
        }
        else {
            std::cout << "Dossier créé avec succès : " << dossier << std::endl;
        }
    }
}

void GestionFichier::sauvegarderConfiguration(const Grille& grille, const std::string& chemin) {
    try {
        std::ofstream fichier(chemin);  // Ouvre le fichier en mode écriture
        if (!fichier) {
            throw std::ios_base::failure("Impossible d'ouvrir le fichier pour la sauvegarde");
        }

        // Sauvegarder les dimensions de la grille à la première ligne
        fichier << grille.getNbLignes() << " " << grille.getNbColonnes() << "\n";

        // Sauvegarder le contenu de la grille dans le fichier
        grille.sauvegarderDansFichier(chemin);

        std::cout << "Configuration sauvegardée dans : " << chemin << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Erreur lors de la sauvegarde de la configuration : " << e.what() << "\n";
    }
}

void GestionFichier::chargerConfiguration(Grille& grille, const std::string& chemin) {
    try {
        grille.initialiserDepuisFichier(chemin); // Appelle directement la méthode de Grille
        std::cout << "Configuration chargée depuis : " << chemin << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Erreur lors du chargement de la configuration : " << e.what() << "\n";
    }
}

void GestionFichier::sauvegarderIteration(const Grille& grille, const std::string& dossier, int iteration) {
    creerDossier(dossier); // Crée le dossier si nécessaire
    std::string cheminFichier = dossier + "/iteration_" + std::to_string(iteration) + ".txt";
    try {
        grille.sauvegarderDansFichier(cheminFichier); // Sauvegarde directement
        std::cout << "Iteration sauvegardée dans : " << cheminFichier << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Erreur lors de la sauvegarde de l'itération : " << e.what() << "\n";
    }
}
