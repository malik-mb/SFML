

# 🌍 Jeu de la Vie 🌟 🧬

Un projet de simulation du célèbre **Jeu de la Vie** de John Conway, implémenté en **C++** avec deux modes : une interface graphique utilisant **SFML** et un mode console. 🎮  

## 📝 Description  

Le **Jeu de la Vie** est un automate cellulaire conçu par le mathématicien **John Conway**. Il simule l'évolution d'une population de cellules vivantes dans une grille selon des règles simples :  

- 🟢 Une cellule **vivante** reste vivante si elle a **2 ou 3 voisins vivants**, sinon elle meurt.  
- ⚫ Une cellule **morte** devient vivante si elle a exactement **3 voisins vivants**.  

Ce projet propose :  
- 🌌 **Mode Console** : Affiche l'évolution de la grille dans le terminal.  
- 🎨 **Mode Graphique** : Visualisation interactive avec SFML.  

---

## 🚀 Fonctionnalités  

### 1️⃣ Modes d'exécution  
- **Mode Console** :  
  - Affiche la grille à chaque génération dans le terminal.  
  - Simplicité et rapidité d'exécution.  

- **Mode Graphique** :  
  - Interface visuelle élégante avec **SFML**.  
  - Contrôle interactif de la vitesse via le clavier (`+` et `-`).  

### 2️⃣ Grille torique  
- Les cellules en bord de grille sont connectées avec celles du côté opposé, créant une grille "circulaire". 🌐  

### 3️⃣ Configuration personnalisable  
- 📏 Taille de la grille.  
- ⏲️ Vitesse d'itération.  
- ♻️ Activation ou non de la grille torique.  

---

## 📂 Structure du projet  

```plaintext
Project2/
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
```

---

## 🛠️ Installation  

### 📋 Prérequis  
- **C++17** ou version ultérieure.  
- **SFML 2.5.1** ou supérieur pour le mode graphique.  

### 💻 Étapes d'installation  

1. Clonez le dépôt GitHub :  
   ```bash
   git clone https://github.com/votre-utilisateur/jeu-de-la-vie.git
   cd jeu-de-la-vie
   ```

2. Installez **SFML** en suivant les instructions [officielles](https://www.sfml-dev.org/).  

3. Compilez le projet :  
   - **Sous Windows** (Visual Studio) : Ouvrez `project.sln` et compilez.  
   - **Sous Linux** :  
     ```bash
     g++ -std=c++17 -o game main.cpp Composants/*.cpp Interface/*.cpp Service/*.cpp -lsfml-graphics -lsfml-window -lsfml-system
     ```

4. Exécutez l'application :  
   - **Windows** :  
     ```cmd
     .\Debug\game.exe
     ```  
   - **Linux** :  
     ```bash
     ./game
     ```  

---

## 📊 Fichier d'entrée  

Pour initialiser la grille, fournissez un fichier d'entrée au format suivant :  

```plaintext
5 5
0 1 0 0 0
1 1 1 0 0
0 0 1 0 0
0 0 0 0 1
0 0 0 0 0
```

- La première ligne indique la taille de la grille (**lignes colonnes**).  
- Les lignes suivantes décrivent l'état initial des cellules :  
  - `1` : cellule vivante.  
  - `0` : cellule morte.  

---

## 🎮 Utilisation  

### 🎲 Choisissez un mode  
1. Mode Console : Tapez `1`.  
2. Mode Graphique : Tapez `2`.  

### 🖥️ Commandes en mode graphique  
| Commande | Action                             |  
|----------|------------------------------------|  
| `+`      | Accélère la simulation.            |  
| `-`      | Ralentit la simulation.            |  
| **Fermer** | Quitte le mode graphique.          |  

---

## 🧪 Tests Unitaires  

Le projet inclut des tests unitaires utilisant **Google Test** pour valider :  
- 🟢 Gestion des cellules (vivante/morte).  
- 📏 Mise à jour et affichage de la grille.  
- ♻️ Application des règles du jeu.  

### 🔧 Exécution des tests  
1. Configurez et compilez les tests.  
2. Lancez-les depuis votre IDE ou en ligne de commande :  
   ```bash
   ./tests
   ```

---

## 🤝 Contributions  

Les contributions sont les bienvenues ! Suivez ces étapes pour participer :  
1. **Forkez** le dépôt.  
2. Créez une branche :  
   ```bash
   git checkout -b ma-nouvelle-fonctionnalite
   ```  
3. Faites vos modifications, puis validez :  
   ```bash
   git commit -m "Ajout d'une nouvelle fonctionnalité"
   ```  
4. Poussez vos changements et ouvrez une **pull request**.  

---

## 📄 Licence  

Ce projet est sous licence MIT. Consultez le fichier [LICENSE](./LICENSE) pour plus de détails.  

---

**Merci d'utiliser le Jeu de la Vie ! Amusez-vous bien avec cette simulation captivante. 🌟**

