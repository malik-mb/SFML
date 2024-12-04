🌟 Jeu de la Vie 🧬
Bienvenue dans le Jeu de la Vie de Conway, un projet amusant et éducatif en C++ avec une interface graphique interactive ! 🎮✨

🚀 Fonctionnalités
🎨 Interface graphique : Visualisez l'évolution des cellules en temps réel.
🛠️ Personnalisable : Choisissez la taille de la grille, les conditions initiales et les règles.
⏱️ Simulation fluide : Jouez avec la vitesse d'évolution des générations.
🔄 Modes multiples : Configurez des motifs classiques ou expérimentez avec vos propres designs.

🎯 Objectif du jeu

Le "Jeu de la Vie" est un automate cellulaire imaginé par John Conway. Chaque cellule de la grille peut être vivante ou morte, et son état change à chaque génération selon des règles simples mais fascinantes :

🟢 Une cellule vivante avec 2 ou 3 voisins reste vivante.
⚫ Une cellule morte avec exactement 3 voisins devient vivante.
☠️ Sinon, la cellule meurt ou reste morte.

🌌 Mode Console : Affiche l'évolution de la grille dans le terminal.
🎨 Mode Graphique : Visualisation interactive avec SFML.

🚀 Fonctionnalités
1️⃣ Modes d'exécution
Mode Console :

Affiche la grille à chaque génération dans le terminal.
Simplicité et rapidité d'exécution.
Mode Graphique :

Interface visuelle élégante avec SFML.
Contrôle interactif de la vitesse via le clavier (+ et -).
2️⃣ Grille torique
Les cellules en bord de grille sont connectées avec celles du côté opposé, créant une grille "circulaire". 🌐
3️⃣ Configuration personnalisable
📏 Taille de la grille.
⏲️ Vitesse d'itération.
♻️ Activation ou non de la grille torique.
📂 Structure du projet


Project
├── Composants/
│   ├── Cell.cpp / Cell.h           # Gestion des cellules
│   ├── Grid.cpp / Grid.h           # Gestion de la grille
├── Interface/
│   ├── GraphicEngine.cpp / .h      # Rendu graphique
│   ├── ModeConsole.cpp / .h        # Mode console
│   ├── ModeGraphique.cpp / .h      # Mode graphique
├── Service/
│   ├── GameOfLife.cpp / .h         # Gestion principale du jeu
├── main.cpp                        # Point d'entrée du programme
└── README.md                       # Documentation

🛠️ Installation
📋 Prérequis
C++17 ou version ultérieure.
SFML 2.5.1 ou supérieur pour le mode graphique.
💻 Étapes d'installation
Clonez le dépôt GitHub :

bash

git clone https://github.com/votre-utilisateur/jeu-de-la-vie.git
cd jeu-de-la-vie
Installez SFML en suivant les instructions officielles.

Compilez le projet :

Sous Windows (Visual Studio) : Ouvrez project.sln et compilez.

Sous Linux :

bash

g++ -std=c++17 -o game main.cpp Composants/*.cpp Interface/*.cpp Service/*.cpp -lsfml-graphics -lsfml-window -lsfml-system

Exécutez l'application :

Windows :
cmd

.\Debug\game.exe
Linux :
bash

./game
📊 Fichier d'entrée
Pour initialiser la grille, fournissez un fichier d'entrée au format suivant :

plaintext

5 5
0 1 0 0 0
1 1 1 0 0
0 0 1 0 0
0 0 0 0 1
0 0 0 0 0
La première ligne indique la taille de la grille (lignes colonnes).

Les lignes suivantes décrivent l'état initial des cellules :
1 : cellule vivante.
0 : cellule morte.

🎮 Utilisation
🎲 Choisissez un mode

Mode Console : Tapez 1.
Mode Graphique : Tapez 2.

🖥️ Commandes en mode graphique
Commande	Action

+	Accélère la simulation.
-	Ralentit la simulation.
  
Fermer	Quitte le mode graphique.
🧪 Tests Unitaires
Le projet inclut des tests unitaires utilisant Google Test pour valider :

🟢 Gestion des cellules (vivante/morte).
📏 Mise à jour et affichage de la grille.
♻️ Application des règles du jeu.
🔧 Exécution des tests
Configurez et compilez les tests.
Lancez-les depuis votre IDE ou en ligne de commande :
bash
Copier le code
./tests
🤝 Contributions
Les contributions sont les bienvenues ! Suivez ces étapes pour participer :

Forkez le dépôt.
Créez une branche :
bash

git checkout -b ma-nouvelle-fonctionnalite
Faites vos modifications, puis validez :
bash

git commit -m "Ajout d'une nouvelle fonctionnalité"
Poussez vos changements et ouvrez une pull request.
