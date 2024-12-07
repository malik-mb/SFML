#include "SFMLInterface.h"
#include <stdexcept>
#include <iostream>

// Initialisation des variables statiques
int SFMLInterface::generation = 0;
int SFMLInterface::nombreMisesAJour = 0;

void SFMLInterface::incrementerMisesAJour() {
    nombreMisesAJour++;
}

void SFMLInterface::resetMisesAJour() {
    nombreMisesAJour = 0;
}

SFMLInterface::SFMLInterface(int largeur, int hauteur, int tailleCellule)
    : tailleCellule(tailleCellule), enPleinEcran(true), enMenu(true), enThemeMenu(false),
    musicPlaying(false), estEnTrainDeModifier(false), nombreIterations(0),
    derniereCelluleModifiee(-1, -1), volume(50.0f), isMuted(false), currentSpeed(50.0f),
    selectedMusic(0) {

    // Initialisation des chemins de musique
    musicPaths = {
        "C:\\Users\\malik\\Downloads\\PNL-Onizuka-_Instrumental_-Instrumentals.ogg",
        "C:\\Users\\malik\\Music\\PNL __ URANUS (instru) - Swann.ogg",
        "C:\\Users\\malik\\Music\\Kekra - Ingé son feat. Alpha Wann, La fève (Instrumental) - 3AFRIT BEAT.ogg"
    };

    musicNames = {
        "PNL - Onizuka",
        "PNL - Uranus",
        "Kekra - Ingé son"
    };

    window.create(sf::VideoMode::getDesktopMode(), "Game Of Life", sf::Style::Fullscreen);
    celluleShape.setSize(sf::Vector2f(tailleCellule - 1, tailleCellule - 1));
    if (!font.loadFromFile("C:\\Users\\malik\\Downloads\\Bungee-Regular.ttf")) {
        std::cerr << "Erreur : Impossible de charger la police." << std::endl;
    }

    // Chargement des textures
    if (!zoomInTexture.loadFromFile("C:\\Users\\malik\\Music\\icons8-zoomer-48.png")) {
        std::cerr << "Erreur : Impossible de charger l'icône de zoom in" << std::endl;
    }
    if (!zoomOutTexture.loadFromFile("C:\\Users\\malik\\Music\\icons8-dézoomer-48.png")) {
        std::cerr << "Erreur : Impossible de charger l'icône de zoom out" << std::endl;
    }
    if (!undoTexture.loadFromFile("C:\\Users\\malik\\Music\\icons8-gauche-2-50.png")) {
        std::cerr << "Erreur : Impossible de charger l'icône undo" << std::endl;
    }
    if (!redoTexture.loadFromFile("C:\\Users\\malik\\Music\\icons8-droit-2-60.png")) {
        std::cerr << "Erreur : Impossible de charger l'icône redo" << std::endl;
    }
    if (!pauseTexture.loadFromFile("C:\\Users\\malik\\Music\\icons8-pause-48.png")) {
        std::cerr << "Erreur : Impossible de charger l'icône de pause" << std::endl;
    }
    if (!playTexture.loadFromFile("C:\\Users\\malik\\Music\\icons8-lecture-50.png")) {
        std::cerr << "Erreur : Impossible de charger l'icône de play" << std::endl;
    }
    if (!resetTexture.loadFromFile("C:\\Users\\malik\\Music\\icons8-mises-à-jour-disponibles-50.png")) {
        std::cerr << "Erreur : Impossible de charger l'icône de reset" << std::endl;
    }
    if (!oscillateurTexture.loadFromFile("C:\\Users\\malik\\Music\\oss.png")) {
        std::cerr << "Erreur : Impossible de charger l'image de l'oscillateur" << std::endl;
    }
    if (!planeurTexture.loadFromFile("C:\\Users\\malik\\Music\\plan.png")) {
        std::cerr << "Erreur : Impossible de charger l'image du planeur" << std::endl;
    }
    if (!canonTexture.loadFromFile("C:\\Users\\malik\\Music\\canon.png")) {
        std::cerr << "Erreur : Impossible de charger l'image du canon" << std::endl;
    }
    if (!muteTexture.loadFromFile("C:\\Users\\malik\\Music\\icons8-muet-64.png")) {
        std::cerr << "Erreur : Impossible de charger l'icône mute" << std::endl;
    }
    if (!soundTexture.loadFromFile("C:\\Users\\malik\\Music\\icons8-son-64.png")) {
        std::cerr << "Erreur : Impossible de charger l'icône son" << std::endl;
    }
    if (!speedTexture.loadFromFile("C:\\Users\\malik\\Music\\icons8-éclair-48.png")) {
        std::cerr << "Erreur : Impossible de charger l'icône de vitesse" << std::endl;
    }
    if (!triskelionTexture.loadFromFile("C:\\Users\\malik\\Music\\icons8-triskelion-100.png")) {
        std::cerr << "Erreur : Impossible de charger l'image du triskelion" << std::endl;
    }

    // Configuration des sprites
    triskelionSprite.setTexture(triskelionTexture);
    zoomInSprite.setTexture(zoomInTexture);
    zoomOutSprite.setTexture(zoomOutTexture);
    undoSprite.setTexture(undoTexture);
    redoSprite.setTexture(redoTexture);
    pauseSprite.setTexture(pauseTexture);
    playSprite.setTexture(playTexture);
    resetSprite.setTexture(resetTexture);
    oscillateurSprite.setTexture(oscillateurTexture);
    planeurSprite.setTexture(planeurTexture);
    canonSprite.setTexture(canonTexture);
    muteSprite.setTexture(muteTexture);
    soundSprite.setTexture(soundTexture);
    speedSprite.setTexture(speedTexture);
    // Redimensionnement des sprites
    float patternSize = 40.0f;
    float scale;

    scale = patternSize / oscillateurSprite.getGlobalBounds().width;
    oscillateurSprite.setScale(scale, scale);
    scale = patternSize / planeurSprite.getGlobalBounds().width;
    planeurSprite.setScale(scale, scale);
    scale = patternSize / canonSprite.getGlobalBounds().width;
    canonSprite.setScale(scale, scale);

    // Redimensionner les icônes de son et de vitesse
    float iconSize = 30.0f;
    scale = iconSize / muteSprite.getGlobalBounds().width;
    muteSprite.setScale(scale, scale);
    scale = iconSize / soundSprite.getGlobalBounds().width;
    soundSprite.setScale(scale, scale);
    scale = iconSize / speedSprite.getGlobalBounds().width;
    speedSprite.setScale(scale, scale);

    float triskelionScale = 1.5f;
    triskelionSprite.setScale(triskelionScale, triskelionScale);
    triskelionSprite.setPosition(
        (window.getSize().x - triskelionSprite.getGlobalBounds().width) / 2,
        titreTexte.getPosition().y + titreTexte.getGlobalBounds().height + 20
    );

    // Configuration des barres de volume et de vitesse
    float barWidth = 100.0f;
    float barHeight = 5.0f;
    float sliderSize = 10.0f;

    volumeBar.setSize(sf::Vector2f(barWidth, barHeight));
    volumeBar.setFillColor(sf::Color(100, 100, 100));
    volumeSlider.setSize(sf::Vector2f(sliderSize, sliderSize));
    volumeSlider.setFillColor(sf::Color::White);

    speedBar.setSize(sf::Vector2f(barWidth, barHeight));
    speedBar.setFillColor(sf::Color(100, 100, 100));
    speedSlider.setSize(sf::Vector2f(sliderSize, sliderSize));
    speedSlider.setFillColor(sf::Color::White);

    // Positionnement des éléments
    float spacing = 20.0f;
    float startX = spacing;
    float patternY = window.getSize().y - BANDE_NOIRE_HAUTEUR / 2 - patternSize / 2;
    float spacingPatterns = 120.0f;
    float controlsY = window.getSize().y - BANDE_NOIRE_HAUTEUR / 2;

    // Position des patterns
    oscillateurSprite.setPosition(startX, patternY);
    planeurSprite.setPosition(startX + spacingPatterns, patternY);
    canonSprite.setPosition(startX + spacingPatterns * 2, patternY);
    resetSprite.setPosition(startX + spacingPatterns * 3, patternY);

    // Configuration des textes de population et génération
    populationTexte.setFont(font);
    populationTexte.setCharacterSize(20);
    populationTexte.setFillColor(sf::Color::White);
    populationTexte.setPosition(
        speedSprite.getPosition().x + 1150,
        controlsY - 10
    );

    titreTexte.setFont(font);
    titreTexte.setString("GAME OF LIFE");
    titreTexte.setCharacterSize(80);
    titreTexte.setFillColor(sf::Color::White);
    titreTexte.setPosition(
        (window.getSize().x - titreTexte.getLocalBounds().width) / 2,
        window.getSize().y / 4
    );

    generationTexte.setFont(font);
    generationTexte.setCharacterSize(20);
    generationTexte.setFillColor(sf::Color::White);
    generationTexte.setPosition(
        resetSprite.getPosition().x + resetSprite.getGlobalBounds().width + 100,
        controlsY - 10
    );
    // Configuration des noms des patterns
    oscillateurNom.setFont(font);
    oscillateurNom.setString("Oscillateur");
    oscillateurNom.setCharacterSize(12);
    oscillateurNom.setFillColor(sf::Color::White);
    oscillateurNom.setPosition(
        oscillateurSprite.getPosition().x,
        oscillateurSprite.getPosition().y - 20
    );

    planeurNom.setFont(font);
    planeurNom.setString("Planeur");
    planeurNom.setCharacterSize(12);
    planeurNom.setFillColor(sf::Color::White);
    planeurNom.setPosition(
        planeurSprite.getPosition().x,
        planeurSprite.getPosition().y - 20
    );

    canonNom.setFont(font);
    canonNom.setString("Canon");
    canonNom.setCharacterSize(12);
    canonNom.setFillColor(sf::Color::White);
    canonNom.setPosition(
        canonSprite.getPosition().x,
        canonSprite.getPosition().y - 20
    );

    // Position des contrôles à droite
    float rightMargin = spacing;

    zoomOutSprite.setPosition(
        window.getSize().x - zoomOutSprite.getGlobalBounds().width - rightMargin,
        controlsY - zoomOutSprite.getGlobalBounds().height / 2
    );

    zoomInSprite.setPosition(
        zoomOutSprite.getPosition().x - zoomInSprite.getGlobalBounds().width - rightMargin,
        controlsY - zoomInSprite.getGlobalBounds().height / 2
    );

    volumeBar.setPosition(
        zoomInSprite.getPosition().x - volumeBar.getSize().x - rightMargin * 2,
        controlsY
    );

    soundSprite.setPosition(
        volumeBar.getPosition().x - soundSprite.getGlobalBounds().width - rightMargin,
        controlsY - soundSprite.getGlobalBounds().height / 2
    );

    muteSprite.setPosition(soundSprite.getPosition());

    speedBar.setPosition(
        soundSprite.getPosition().x - speedBar.getSize().x - rightMargin * 2,
        controlsY
    );

    speedSprite.setPosition(
        speedBar.getPosition().x - speedSprite.getGlobalBounds().width - rightMargin,
        controlsY - speedSprite.getGlobalBounds().height / 2
    );

    // Position des contrôles au centre
    float centerX = window.getSize().x / 2;

    undoSprite.setPosition(
        centerX - undoSprite.getGlobalBounds().width - spacing * 2,
        controlsY - undoSprite.getGlobalBounds().height / 2
    );

    pauseSprite.setPosition(
        centerX - pauseSprite.getGlobalBounds().width / 2,
        controlsY - pauseSprite.getGlobalBounds().height / 2
    );

    playSprite.setPosition(
        centerX - playSprite.getGlobalBounds().width / 2,
        controlsY - playSprite.getGlobalBounds().height / 2
    );

    redoSprite.setPosition(
        centerX + spacing * 2,
        controlsY - redoSprite.getGlobalBounds().height / 2
    );
    // Configuration des textes des raccourcis
    oscillateurTexte.setFont(font);
    oscillateurTexte.setString("Press O");
    oscillateurTexte.setCharacterSize(12);
    oscillateurTexte.setFillColor(sf::Color::White);
    oscillateurTexte.setPosition(
        oscillateurSprite.getPosition().x,
        oscillateurSprite.getPosition().y + oscillateurSprite.getGlobalBounds().height + 5
    );

    planeurTexte.setFont(font);
    planeurTexte.setString("Press P");
    planeurTexte.setCharacterSize(12);
    planeurTexte.setFillColor(sf::Color::White);
    planeurTexte.setPosition(
        planeurSprite.getPosition().x,
        planeurSprite.getPosition().y + planeurSprite.getGlobalBounds().height + 5
    );

    canonTexte.setFont(font);
    canonTexte.setString("Press C");
    canonTexte.setCharacterSize(12);
    canonTexte.setFillColor(sf::Color::White);
    canonTexte.setPosition(
        canonSprite.getPosition().x,
        canonSprite.getPosition().y + canonSprite.getGlobalBounds().height + 5
    );

    updateVolumeSlider();
    updateSpeedSlider();

    // Configuration de la musique
    try {
        if (menuMusic.openFromFile(musicPaths[selectedMusic])) {
            menuMusic.setLoop(true);
            menuMusic.setVolume(volume);
            menuMusic.play();
            musicPlaying = true;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Erreur lors du chargement de la musique : " << e.what() << std::endl;
    }

    // Configuration du menu
    titreTexte.setFont(font);
    titreTexte.setString("GAME OF LIFE");
    titreTexte.setCharacterSize(50);
    titreTexte.setFillColor(sf::Color::White);
    titreTexte.setPosition(
        (window.getSize().x - titreTexte.getLocalBounds().width) / 2,
        window.getSize().y / 4
    );

    const float boutonLargeur = 200;
    const float boutonHauteur = 60;
    const float espacementBoutons = 60;
    const float centreX = window.getSize().x / 2;
    const float premierBoutonY = window.getSize().y / 2;

    boutonStart.setSize(sf::Vector2f(boutonLargeur, boutonHauteur));
    boutonStart.setFillColor(sf::Color(50, 150, 50));
    boutonStart.setPosition(centreX - boutonLargeur / 2, premierBoutonY);

    boutonParams.setSize(sf::Vector2f(boutonLargeur, boutonHauteur));
    boutonParams.setFillColor(sf::Color(50, 150, 50));
    boutonParams.setPosition(centreX - boutonLargeur / 2, premierBoutonY + boutonHauteur + espacementBoutons);

    boutonTutorial.setSize(sf::Vector2f(boutonLargeur, boutonHauteur));
    boutonTutorial.setFillColor(sf::Color(50, 150, 50));
    boutonTutorial.setPosition(centreX - boutonLargeur / 2, premierBoutonY + (boutonHauteur + espacementBoutons) * 2);

    boutonExit.setSize(sf::Vector2f(boutonLargeur, boutonHauteur));
    boutonExit.setFillColor(sf::Color(50, 150, 50));
    boutonExit.setPosition(centreX - boutonLargeur / 2, premierBoutonY + (boutonHauteur + espacementBoutons) * 3);
    startTexte.setFont(font);
    startTexte.setString("START");
    startTexte.setCharacterSize(30);
    startTexte.setFillColor(sf::Color::White);
    startTexte.setPosition(
        centreX - startTexte.getLocalBounds().width / 2,
        premierBoutonY + (boutonHauteur - startTexte.getLocalBounds().height) / 2
    );

    paramsTexte.setFont(font);
    paramsTexte.setString("THEME");
    paramsTexte.setCharacterSize(30);
    paramsTexte.setFillColor(sf::Color::White);
    paramsTexte.setPosition(
        centreX - paramsTexte.getLocalBounds().width / 2,
        premierBoutonY + boutonHauteur + espacementBoutons + (boutonHauteur - paramsTexte.getLocalBounds().height) / 2
    );

    tutorialTexte.setFont(font);
    tutorialTexte.setString("TUTORIAL");
    tutorialTexte.setCharacterSize(30);
    tutorialTexte.setFillColor(sf::Color::White);
    tutorialTexte.setPosition(
        centreX - tutorialTexte.getLocalBounds().width / 2,
        premierBoutonY + (boutonHauteur + espacementBoutons) * 2 + (boutonHauteur - tutorialTexte.getLocalBounds().height) / 2
    );

    exitTexte.setFont(font);
    exitTexte.setString("EXIT");
    exitTexte.setCharacterSize(30);
    exitTexte.setFillColor(sf::Color::White);
    exitTexte.setPosition(
        centreX - exitTexte.getLocalBounds().width / 2,
        premierBoutonY + (boutonHauteur + espacementBoutons) * 3 + (boutonHauteur - exitTexte.getLocalBounds().height) / 2
    );
}

void SFMLInterface::afficherThemeMenu() {
    window.clear(sf::Color(11, 13, 30));

    float centreX = window.getSize().x / 2;
    float startY = window.getSize().y / 3;
    float spacing = 80.0f;

    // Effet de grille en arrière-plan
    static float gridOffset = 0.0f;
    gridOffset += 0.5f;
    for (float x = -100; x < window.getSize().x + 100; x += 50) {
        for (float y = -100; y < window.getSize().y + 100; y += 50) {
            sf::RectangleShape gridPoint(sf::Vector2f(2, 2));
            float xPos = x + std::sin((y + gridOffset) * 0.02f) * 10;
            gridPoint.setPosition(xPos, y);
            gridPoint.setFillColor(sf::Color(0, 157, 255, 20));
            window.draw(gridPoint);
        }
    }

    // Éléments décoratifs sur les côtés
    // Cercles connectés à gauche
    static std::vector<sf::CircleShape> leftCircles;
    static std::vector<float> leftCirclesPulse;
    if (leftCircles.empty()) {
        for (int i = 0; i < 5; i++) {
            sf::CircleShape circle(20.f);
            circle.setPosition(50.f, 150.f + i * 120.f);
            circle.setFillColor(sf::Color::Transparent);
            circle.setOutlineThickness(2.f);
            leftCircles.push_back(circle);
            leftCirclesPulse.push_back(static_cast<float>(rand()) / RAND_MAX * 6.28f);
        }
    }

    // Lignes verticales décoratives
    sf::RectangleShape leftLine(sf::Vector2f(2.f, window.getSize().y));
    leftLine.setPosition(100.f, 0);
    leftLine.setFillColor(sf::Color(0, 157, 255, 40));
    window.draw(leftLine);

    sf::RectangleShape rightLine(sf::Vector2f(2.f, window.getSize().y));
    rightLine.setPosition(window.getSize().x - 100.f, 0);
    rightLine.setFillColor(sf::Color(0, 157, 255, 40));
    window.draw(rightLine);

    // Animation des cercles et connexions
    for (size_t i = 0; i < leftCircles.size(); i++) {
        leftCirclesPulse[i] += 0.02f;
        float pulsation = (std::sin(leftCirclesPulse[i]) + 1.f) / 2.f;

        leftCircles[i].setOutlineColor(sf::Color(0, 157, 255,
            static_cast<sf::Uint8>(100 + 155 * pulsation)));

        window.draw(leftCircles[i]);

        // Lignes horizontales connectant les cercles
        sf::RectangleShape connector(sf::Vector2f(40.f, 2.f));
        connector.setPosition(leftCircles[i].getPosition().x + 40.f,
            leftCircles[i].getPosition().y + 20.f);
        connector.setFillColor(sf::Color(0, 157, 255,
            static_cast<sf::Uint8>(40 + 60 * pulsation)));
        window.draw(connector);

        // Texte décoratif
        sf::Text decorText;
        decorText.setFont(font);
        decorText.setString(std::to_string(i + 1) + ".0");
        decorText.setCharacterSize(15);
        decorText.setFillColor(sf::Color(0, 157, 255,
            static_cast<sf::Uint8>(100 + 155 * pulsation)));
        decorText.setPosition(
            leftCircles[i].getPosition().x - 40.f,
            leftCircles[i].getPosition().y + 10.f
        );
        window.draw(decorText);
    }
    // Éléments décoratifs à droite
    static std::vector<sf::RectangleShape> rightBars;
    static std::vector<float> rightBarsPulse;
    if (rightBars.empty()) {
        for (int i = 0; i < 8; i++) {
            sf::RectangleShape bar(sf::Vector2f(30.f, 3.f));
            bar.setPosition(window.getSize().x - 90.f, 100.f + i * 80.f);
            rightBars.push_back(bar);
            rightBarsPulse.push_back(static_cast<float>(rand()) / RAND_MAX * 6.28f);
        }
    }

    // Animation des barres droites
    for (size_t i = 0; i < rightBars.size(); i++) {
        rightBarsPulse[i] += 0.03f;
        float pulsation = (std::sin(rightBarsPulse[i]) + 1.f) / 2.f;

        rightBars[i].setFillColor(sf::Color(0, 157, 255,
            static_cast<sf::Uint8>(100 + 155 * pulsation)));

        // Variation de la longueur des barres
        float baseWidth = 30.f;
        float extraWidth = 20.f * pulsation;
        rightBars[i].setSize(sf::Vector2f(baseWidth + extraWidth, 3.f));

        window.draw(rightBars[i]);

        // Points décoratifs
        sf::CircleShape dot(2.f);
        dot.setPosition(
            rightBars[i].getPosition().x + baseWidth + extraWidth + 10.f,
            rightBars[i].getPosition().y - 1.f
        );
        dot.setFillColor(sf::Color(0, 157, 255,
            static_cast<sf::Uint8>(100 + 155 * pulsation)));
        window.draw(dot);
    }

    // Motif hexagonal décoratif
    static float hexRotation = 0.f;
    hexRotation += 0.2f;

    sf::CircleShape hexagon(40.f, 6);
    hexagon.setPosition(window.getSize().x - 150.f, 50.f);
    hexagon.setFillColor(sf::Color::Transparent);
    hexagon.setOutlineThickness(2.f);
    hexagon.setOutlineColor(sf::Color(0, 157, 255, 100));
    hexagon.setRotation(hexRotation);
    window.draw(hexagon);

    // Petit hexagone intérieur
    sf::CircleShape innerHex(20.f, 6);
    innerHex.setPosition(window.getSize().x - 130.f, 70.f);
    innerHex.setFillColor(sf::Color::Transparent);
    innerHex.setOutlineThickness(2.f);
    innerHex.setOutlineColor(sf::Color(0, 157, 255, 100));
    innerHex.setRotation(-hexRotation);
    window.draw(innerHex);

    // Effet de lignes dynamiques
    static std::vector<sf::VertexArray> lines;
    if (lines.empty()) {
        for (int i = 0; i < 5; i++) {
            sf::VertexArray line(sf::Lines, 2);
            line[0].position = sf::Vector2f(0, rand() % window.getSize().y);
            line[1].position = sf::Vector2f(window.getSize().x, rand() % window.getSize().y);
            line[0].color = sf::Color(0, 157, 255, 30);
            line[1].color = sf::Color(0, 157, 255, 30);
            lines.push_back(line);
        }
    }

    // Animation des lignes
    static float lineOffset = 0.0f;
    lineOffset += 0.5f;
    for (auto& line : lines) {
        float y1 = line[0].position.y + std::sin(lineOffset * 0.02f) * 50;
        float y2 = line[1].position.y + std::cos(lineOffset * 0.02f) * 50;
        line[0].position.y = y1;
        line[1].position.y = y2;
        window.draw(line);
    }

    // Effet de particules optimisé
    static std::vector<sf::CircleShape> particles;
    static std::vector<sf::Vector2f> particleVelocities;
    // Initialisation des particules
    if (particles.empty()) {
        for (int i = 0; i < 30; i++) {
            sf::CircleShape particle;
            particle.setRadius(1.5f);
            particle.setPosition(
                static_cast<float>(rand() % window.getSize().x),
                static_cast<float>(rand() % window.getSize().y)
            );
            particle.setFillColor(sf::Color(0, 157, 255, 40));
            particles.push_back(particle);

            float angle = static_cast<float>(rand() % 360) * 3.14159f / 180.0f;
            float speed = 0.5f;
            particleVelocities.push_back(sf::Vector2f(
                std::cos(angle) * speed,
                std::sin(angle) * speed
            ));
        }
    }

    // Animation des particules
    for (size_t i = 0; i < particles.size(); i++) {
        particles[i].move(particleVelocities[i]);

        if (particles[i].getPosition().x < 0)
            particles[i].setPosition(window.getSize().x, particles[i].getPosition().y);
        if (particles[i].getPosition().x > window.getSize().x)
            particles[i].setPosition(0, particles[i].getPosition().y);
        if (particles[i].getPosition().y < 0)
            particles[i].setPosition(particles[i].getPosition().x, window.getSize().y);
        if (particles[i].getPosition().y > window.getSize().y)
            particles[i].setPosition(particles[i].getPosition().x, 0);

        window.draw(particles[i]);
    }

    // Effet de pulsation amélioré
    static float pulseTimer = 0.0f;
    pulseTimer += 0.03f;
    float pulseFactor = (std::sin(pulseTimer) + 1.0f) / 2.0f;

    // Logo animé
    static sf::CircleShape logo(40.f);
    logo.setPosition(centreX - 40.f, 50.f);
    logo.setFillColor(sf::Color::Transparent);
    logo.setOutlineThickness(2.f);
    logo.setOutlineColor(sf::Color(0, 157, 255, static_cast<sf::Uint8>(100 + 155 * pulseFactor)));

    static float rotation = 0.0f;
    rotation += 0.5f;
    logo.setRotation(rotation);
    window.draw(logo);

    // Titre avec effet de glitch
    sf::Text titreTheme;
    titreTheme.setFont(font);
    titreTheme.setString("SELECTION THEME");
    titreTheme.setCharacterSize(50);

    static int glitchOffset = 0;
    if (rand() % 30 == 0) {
        glitchOffset = (rand() % 3) - 1;
    }

    sf::Text titreBordure = titreTheme;
    titreBordure.setFillColor(sf::Color(0, 157, 255));
    titreBordure.setOutlineThickness(3);
    titreBordure.setOutlineColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(128 + 127 * pulseFactor)));
    titreBordure.setPosition(
        centreX - titreBordure.getLocalBounds().width / 2,
        startY - 100
    );

    sf::Text titreGlitch = titreBordure;
    titreGlitch.setFillColor(sf::Color(255, 0, 100, 50));
    titreGlitch.setPosition(
        titreBordure.getPosition().x + glitchOffset,
        titreBordure.getPosition().y
    );

    window.draw(titreGlitch);
    window.draw(titreBordure);

    // Récupération position souris
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    // Options de musique avec effets améliorés
    for (size_t i = 0; i < musicNames.size(); i++) {
        sf::RectangleShape cadre;
        float cadreWidth = 350.0f;
        float cadreHeight = 60.0f;
        cadre.setSize(sf::Vector2f(cadreWidth, cadreHeight));
        cadre.setPosition(
            centreX - cadreWidth / 2,
            startY + i * spacing - 15
        );
        cadre.setFillColor(sf::Color(20, 20, 40, 200));
        cadre.setOutlineThickness(2);

        // Effet de brillance pour l'option sélectionnée
        if (i == selectedMusic) {
            sf::RectangleShape glow = cadre;
            glow.setFillColor(sf::Color::Transparent);
            glow.setOutlineThickness(4);
            glow.setOutlineColor(sf::Color(0, 157, 255, static_cast<sf::Uint8>(50 + 100 * pulseFactor)));
            window.draw(glow);

            cadre.setOutlineColor(sf::Color(0, 157, 255));
        }
        else {
            cadre.setOutlineColor(sf::Color(100, 100, 100));
        }

        // Icône de musique animée
        static float noteRotation = 0.0f;
        noteRotation += 0.5f;

        sf::CircleShape musicIcon(10.f, 3);
        musicIcon.setPosition(
            cadre.getPosition().x + 20,
            cadre.getPosition().y + cadreHeight / 2 - 10
        );
        musicIcon.setRotation(noteRotation);
        musicIcon.setFillColor(i == selectedMusic ? sf::Color(0, 157, 255) : sf::Color(150, 150, 150));

        // Texte de l'option
        sf::Text musicOption;
        musicOption.setFont(font);
        musicOption.setString(musicNames[i]);
        musicOption.setCharacterSize(30);
        musicOption.setFillColor(i == selectedMusic ? sf::Color(0, 157, 255) : sf::Color::White);
        musicOption.setPosition(
            centreX - musicOption.getLocalBounds().width / 2,
            startY + i * spacing
        );

        // Effet de survol
        if (cadre.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            cadre.setFillColor(sf::Color(40, 40, 60, 200));
            musicOption.setFillColor(sf::Color(0, 255, 255));
            musicIcon.setFillColor(sf::Color(0, 255, 255));

            // Particules au survol
            if (rand() % 10 == 0) {
                sf::CircleShape hoverParticle;
                hoverParticle.setRadius(1.0f);
                hoverParticle.setPosition(
                    cadre.getPosition().x + rand() % static_cast<int>(cadreWidth),
                    cadre.getPosition().y + cadreHeight
                );
                hoverParticle.setFillColor(sf::Color(0, 255, 255, 100));
                window.draw(hoverParticle);
            }

            // Ligne d'énergie au survol
            sf::RectangleShape energyLine(sf::Vector2f(cadreWidth, 2.f));
            energyLine.setPosition(cadre.getPosition().x, cadre.getPosition().y + cadreHeight - 2);
            energyLine.setFillColor(sf::Color(0, 255, 255, static_cast<sf::Uint8>(100 + 155 * pulseFactor)));
            window.draw(energyLine);
        }

        window.draw(cadre);
        window.draw(musicIcon);
        window.draw(musicOption);
    }

    // Séparateur animé
    float themeStartY = startY + (musicNames.size() + 1) * spacing;

    sf::RectangleShape separator(sf::Vector2f(400.f, 2.f));
    separator.setPosition(centreX - 200.f, themeStartY - spacing / 2);
    separator.setFillColor(sf::Color(100, 100, 100));
    window.draw(separator);

    // Effet de gradient sur le séparateur
    float gradientPos = (std::sin(pulseTimer * 2) + 1.0f) / 2.0f * 400.f;
    sf::RectangleShape separatorGlow(sf::Vector2f(100.f, 2.f));
    separatorGlow.setPosition(centreX - 200.f + gradientPos, themeStartY - spacing / 2);
    separatorGlow.setFillColor(sf::Color(0, 157, 255));
    window.draw(separatorGlow);
    // Options de thème avec effets améliorés
    for (size_t i = 0; i < themeNames.size(); i++) {
        sf::RectangleShape themeCadre;
        float cadreWidth = 350.0f;
        float cadreHeight = 60.0f;
        themeCadre.setSize(sf::Vector2f(cadreWidth, cadreHeight));
        themeCadre.setPosition(
            centreX - cadreWidth / 2,
            themeStartY + i * spacing - 15
        );
        themeCadre.setFillColor(sf::Color(20, 20, 40, 200));
        themeCadre.setOutlineThickness(2);

        // Couleurs selon le thème
        sf::Color themeColor;
        switch (i) {
        case 0: themeColor = sf::Color(0, 157, 255); break;  // BLUE
        case 1: themeColor = sf::Color(0, 255, 50); break;   // GREEN
        case 2: themeColor = sf::Color(255, 0, 31); break;   // RED
        }

        // Effet de sélection
        if (i == static_cast<int>(currentTheme)) {
            // Effet de halo
            sf::RectangleShape glow = themeCadre;
            glow.setFillColor(sf::Color::Transparent);
            glow.setOutlineThickness(4);
            glow.setOutlineColor(sf::Color(
                themeColor.r,
                themeColor.g,
                themeColor.b,
                static_cast<sf::Uint8>(50 + 100 * pulseFactor)
            ));
            window.draw(glow);

            themeCadre.setOutlineColor(themeColor);

            // Particules d'énergie pour le thème sélectionné
            if (rand() % 20 == 0) {
                sf::CircleShape energyParticle(2.f);
                energyParticle.setPosition(
                    themeCadre.getPosition().x + rand() % static_cast<int>(cadreWidth),
                    themeCadre.getPosition().y + rand() % static_cast<int>(cadreHeight)
                );
                energyParticle.setFillColor(sf::Color(
                    themeColor.r,
                    themeColor.g,
                    themeColor.b,
                    100
                ));
                window.draw(energyParticle);
            }
        }
        else {
            themeCadre.setOutlineColor(sf::Color(100, 100, 100));
        }

        // Icône du thème avec animation
        sf::CircleShape themeIcon(15.f);
        themeIcon.setPosition(
            themeCadre.getPosition().x + 20,
            themeCadre.getPosition().y + cadreHeight / 2 - 15
        );
        themeIcon.setFillColor(themeColor);

        // Animation de l'icône
        if (i == static_cast<int>(currentTheme)) {
            float scale = 1.0f + 0.1f * pulseFactor;
            themeIcon.setScale(scale, scale);
        }

        sf::Text themeOption;
        themeOption.setFont(font);
        themeOption.setString(themeNames[i]);
        themeOption.setCharacterSize(30);
        themeOption.setFillColor(i == static_cast<int>(currentTheme) ? themeColor : sf::Color::White);
        themeOption.setPosition(
            centreX - themeOption.getLocalBounds().width / 2,
            themeStartY + i * spacing
        );

        // Effet de survol
        if (themeCadre.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            themeCadre.setFillColor(sf::Color(40, 40, 60, 200));
            themeOption.setFillColor(sf::Color(0, 255, 255));

            // Ligne d'énergie au survol
            sf::RectangleShape energyLine(sf::Vector2f(cadreWidth, 2.f));
            energyLine.setPosition(themeCadre.getPosition().x, themeCadre.getPosition().y + cadreHeight - 2);
            energyLine.setFillColor(sf::Color(0, 255, 255, static_cast<sf::Uint8>(100 + 155 * pulseFactor)));
            window.draw(energyLine);
        }

        window.draw(themeCadre);
        window.draw(themeIcon);
        window.draw(themeOption);
    }

    // Effet de scan-lines
    for (int y = 0; y < window.getSize().y; y += 4) {
        sf::RectangleShape scanLine(sf::Vector2f(window.getSize().x, 1));
        scanLine.setPosition(0, y);
        scanLine.setFillColor(sf::Color(255, 255, 255, 3));
        window.draw(scanLine);
    }

    // Effet de vignette final
    sf::RectangleShape vignette;
    vignette.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    vignette.setPosition(0, 0);
    float vignetteIntensity = 0.3f + 0.1f * pulseFactor;
    sf::Color vignetteColor(0, 0, 20, static_cast<sf::Uint8>(200 * vignetteIntensity));
    vignette.setFillColor(vignetteColor);
    window.draw(vignette);
    sf::RectangleShape retourCadre;
    float retourWidth = 250.0f;
    float retourHeight = 50.0f;
    retourCadre.setSize(sf::Vector2f(retourWidth, retourHeight));
    retourCadre.setPosition(
        centreX - retourWidth / 2,
        themeStartY + themeNames.size() * spacing + 45
    );
    retourCadre.setFillColor(sf::Color(20, 20, 40, 200));
    retourCadre.setOutlineThickness(2);
    retourCadre.setOutlineColor(sf::Color(100, 100, 100));

    sf::Text retourTexte;
    retourTexte.setFont(font);
    retourTexte.setString("RETOUR");
    retourTexte.setCharacterSize(30);
    retourTexte.setFillColor(sf::Color::White);
    retourTexte.setPosition(
        centreX - retourTexte.getLocalBounds().width / 2,
        themeStartY + themeNames.size() * spacing + 55
    );

    // Effet de survol sur le bouton retour
    if (retourCadre.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        retourCadre.setFillColor(sf::Color(40, 40, 60, 200));
        retourTexte.setFillColor(sf::Color(0, 255, 255));

        // Effet de brillance
        sf::RectangleShape retourGlow = retourCadre;
        retourGlow.setFillColor(sf::Color::Transparent);
        retourGlow.setOutlineThickness(4);
        retourGlow.setOutlineColor(sf::Color(0, 157, 255, static_cast<sf::Uint8>(50 + 100 * pulseFactor)));
        window.draw(retourGlow);

        // Particules au survol
        if (rand() % 10 == 0) {
            sf::CircleShape hoverParticle;
            hoverParticle.setRadius(1.0f);
            hoverParticle.setPosition(
                retourCadre.getPosition().x + rand() % static_cast<int>(retourWidth),
                retourCadre.getPosition().y + retourHeight
            );
            hoverParticle.setFillColor(sf::Color(0, 255, 255, 100));
            window.draw(hoverParticle);
        }

        // Ligne d'énergie au survol
        sf::RectangleShape energyLine(sf::Vector2f(retourWidth, 2.f));
        energyLine.setPosition(retourCadre.getPosition().x, retourCadre.getPosition().y + retourHeight - 2);
        energyLine.setFillColor(sf::Color(0, 255, 255, static_cast<sf::Uint8>(100 + 155 * pulseFactor)));
        window.draw(energyLine);
    }

    // Petites flèches animées à côté du bouton retour
    static float arrowOffset = 0.0f;
    arrowOffset += 0.1f;
    float arrowPulse = (std::sin(arrowOffset) + 1.0f) / 2.0f;

    for (int i = 0; i < 2; i++) {
        sf::ConvexShape arrow;
        arrow.setPointCount(3);
        arrow.setPoint(0, sf::Vector2f(0, 0));
        arrow.setPoint(1, sf::Vector2f(15, 10));
        arrow.setPoint(2, sf::Vector2f(0, 20));
        arrow.setFillColor(sf::Color(0, 157, 255, static_cast<sf::Uint8>(100 + 155 * arrowPulse)));

        float xPos = retourCadre.getPosition().x - 30.f - (i * 20.f) - (arrowPulse * 5.f);
        arrow.setPosition(xPos, retourCadre.getPosition().y + 15);
        window.draw(arrow);
    }

    window.draw(retourCadre);
    window.draw(retourTexte);
    window.display();
}

void SFMLInterface::afficherMenu() {
    if (enThemeMenu) {
        afficherThemeMenu();
        return;
    }

    window.clear(sf::Color(11, 13, 30));

    // Fonction helper pour les décorations latérales
    auto drawSideDecoration = [this](float x, float y, bool isLeft) {
        // Ligne verticale principale
        sf::RectangleShape mainLine(sf::Vector2f(2.f, 600.f));
        mainLine.setPosition(x, y);
        mainLine.setFillColor(sf::Color(0, 157, 255, 100));
        window.draw(mainLine);

        // Plusieurs colonnes de décorations
        for (int col = 0; col < 3; col++) {
            float xOffset = isLeft ? (col * 40.f) : (-col * 40.f - 40.f);

            // Lignes horizontales
            for (int i = 0; i < 10; i++) {
                sf::RectangleShape hLine(sf::Vector2f(30.f, 2.f));
                float yOffset = i * 65.f;
                hLine.setPosition(x + xOffset, y + yOffset);
                hLine.setFillColor(sf::Color(0, 157, 255, 100));
                window.draw(hLine);

                // Points décoratifs
                sf::CircleShape point(2.f);
                point.setFillColor(sf::Color(0, 255, 255, 150));
                point.setPosition(
                    x + xOffset + (isLeft ? 30.f : -4.f),
                    y + yOffset - 2.f
                );
                window.draw(point);

                // Rectangles décoratifs
                if (i % 2 == 0) {
                    sf::RectangleShape rect(sf::Vector2f(15.f, 8.f));
                    rect.setPosition(
                        x + xOffset + (isLeft ? 35.f : -20.f),
                        y + yOffset - 3.f
                    );
                    rect.setFillColor(sf::Color(0, 157, 255, 50));
                    window.draw(rect);
                }
            }

            // Lignes verticales secondaires
            sf::RectangleShape vLine(sf::Vector2f(2.f, 580.f));
            vLine.setPosition(x + xOffset + (isLeft ? 30.f : 0.f), y + 10.f);
            vLine.setFillColor(sf::Color(0, 157, 255, 70));
            window.draw(vLine);

            // Hexagones décoratifs
            for (int i = 0; i < 5; i++) {
                sf::CircleShape hexagon(10.f, 6);
                hexagon.setPosition(
                    x + xOffset + (isLeft ? 10.f : -20.f),
                    y + i * 140.f + 20.f
                );
                hexagon.setFillColor(sf::Color(0, 0, 0, 0));
                hexagon.setOutlineColor(sf::Color(0, 157, 255, 100));
                hexagon.setOutlineThickness(1.f);
                hexagon.setRotation(30.f);
                window.draw(hexagon);
            }
        }
        // Motifs triangulaires
        for (int i = 0; i < 8; i++) {
            sf::ConvexShape triangle;
            triangle.setPointCount(3);
            float size = 15.f;
            triangle.setPoint(0, sf::Vector2f(0, 0));
            triangle.setPoint(1, sf::Vector2f(size, size / 2));
            triangle.setPoint(2, sf::Vector2f(0, size));

            triangle.setPosition(
                x + (isLeft ? 120.f : -140.f),
                y + i * 80.f + 20.f
            );
            triangle.setFillColor(sf::Color(0, 157, 255, 50));
            triangle.setRotation(isLeft ? 0.f : 180.f);
            window.draw(triangle);
        }

        // Cercles pulsants
        static float pulse = 0.0f;
        pulse += 0.05f;
        for (int i = 0; i < 4; i++) {
            float radius = 8.f + std::sin(pulse + i) * 2.f;
            sf::CircleShape circle(radius);
            circle.setPosition(
                x + (isLeft ? 140.f : -160.f),
                y + i * 160.f + 40.f
            );
            circle.setFillColor(sf::Color(0, 157, 255, 30));
            circle.setOutlineColor(sf::Color(0, 255, 255, 100));
            circle.setOutlineThickness(1.f);
            window.draw(circle);
        }

        // Lignes diagonales
        for (int i = 0; i < 15; i++) {
            sf::RectangleShape diagLine(sf::Vector2f(20.f, 1.f));
            diagLine.setPosition(
                x + (isLeft ? 90.f : -110.f),
                y + i * 40.f + 10.f
            );
            diagLine.setRotation(isLeft ? 45.f : -45.f);
            diagLine.setFillColor(sf::Color(0, 157, 255, 70));
            window.draw(diagLine);
        }
        };

    // Effet de nébuleuse en arrière-plan
    static std::vector<sf::CircleShape> nebulaPoints;
    static std::vector<float> nebulaPhases;
    if (nebulaPoints.empty()) {
        for (int i = 0; i < 200; i++) {
            sf::CircleShape point(rand() % 3 + 1);
            point.setPosition(
                rand() % window.getSize().x,
                rand() % window.getSize().y
            );
            point.setFillColor(sf::Color(
                0,
                rand() % 100 + 157,
                rand() % 100 + 155,
                rand() % 100 + 50
            ));
            nebulaPoints.push_back(point);
            nebulaPhases.push_back(static_cast<float>(rand()) / RAND_MAX * 6.28f);
        }
    }

    // Animation de la nébuleuse
    static float nebulaTime = 0.0f;
    nebulaTime += 0.01f;
    for (size_t i = 0; i < nebulaPoints.size(); i++) {
        nebulaPhases[i] += 0.01f;
        float xOffset = std::sin(nebulaPhases[i]) * 2;
        float yOffset = std::cos(nebulaPhases[i]) * 2;
        nebulaPoints[i].move(xOffset, yOffset);

        float scale = 1.0f + std::sin(nebulaTime + nebulaPhases[i]) * 0.2f;
        nebulaPoints[i].setScale(scale, scale);

        sf::Color color = nebulaPoints[i].getFillColor();
        color.a = static_cast<sf::Uint8>(100 + 50 * std::sin(nebulaTime + nebulaPhases[i]));
        nebulaPoints[i].setFillColor(color);

        window.draw(nebulaPoints[i]);
    }
    // Effet de grille en arrière-plan avec ondulation
    static float gridOffset = 0.0f;
    static float waveTime = 0.0f;
    gridOffset += 0.5f;
    waveTime += 0.02f;

    for (float x = -100; x < window.getSize().x + 100; x += 50) {
        for (float y = -100; y < window.getSize().y + 100; y += 50) {
            sf::RectangleShape gridPoint(sf::Vector2f(2, 2));
            float waveOffset = std::sin(waveTime + x * 0.01f) * 20;
            float xPos = x + std::sin((y + gridOffset) * 0.02f) * 10 + waveOffset;
            gridPoint.setPosition(xPos, y);
            gridPoint.setFillColor(sf::Color(0, 157, 255, 20));
            window.draw(gridPoint);
        }
    }

    // Effet de lignes énergétiques
    static std::vector<sf::VertexArray> energyLines;
    static std::vector<float> linePhases;
    if (energyLines.empty()) {
        for (int i = 0; i < 10; i++) {
            sf::VertexArray line(sf::Lines, 2);
            line[0].position = sf::Vector2f(0, rand() % window.getSize().y);
            line[1].position = sf::Vector2f(window.getSize().x, rand() % window.getSize().y);
            line[0].color = sf::Color(0, 157, 255, 50);
            line[1].color = sf::Color(0, 157, 255, 50);
            energyLines.push_back(line);
            linePhases.push_back(static_cast<float>(rand()) / RAND_MAX * 6.28f);
        }
    }

    // Animation des lignes énergétiques
    static float lineTime = 0.0f;
    lineTime += 0.02f;
    for (size_t i = 0; i < energyLines.size(); i++) {
        linePhases[i] += 0.01f;
        float yOffset = std::sin(lineTime + linePhases[i]) * 50;
        energyLines[i][0].position.y = energyLines[i][0].position.y + yOffset;
        energyLines[i][1].position.y = energyLines[i][1].position.y + yOffset;

        sf::Uint8 alpha = static_cast<sf::Uint8>(30 + 20 * std::sin(lineTime + linePhases[i]));
        energyLines[i][0].color.a = alpha;
        energyLines[i][1].color.a = alpha;

        window.draw(energyLines[i]);
    }

    // Cercles décoratifs animés
    static std::vector<sf::CircleShape> decorativeCircles;
    static std::vector<float> circlePhases;
    if (decorativeCircles.empty()) {
        for (int i = 0; i < 3; i++) {
            sf::CircleShape circle(100.f);
            circle.setFillColor(sf::Color::Transparent);
            circle.setOutlineThickness(2.f);
            circle.setPosition(window.getSize().x * 0.2f * (i + 1), -50.f);
            decorativeCircles.push_back(circle);
            circlePhases.push_back(static_cast<float>(rand()) / RAND_MAX * 6.28f);
        }
    }

    // Animation des cercles
    for (size_t i = 0; i < decorativeCircles.size(); i++) {
        circlePhases[i] += 0.02f;
        float alpha = (std::sin(circlePhases[i]) + 1.f) / 2.f * 100.f;
        decorativeCircles[i].setOutlineColor(sf::Color(0, 157, 255, static_cast<sf::Uint8>(alpha)));
        decorativeCircles[i].setRotation(circlePhases[i] * 30);
        window.draw(decorativeCircles[i]);
    }
    // Animation du titre avec effets
    static float titlePulse = 0.0f;
    static float titleDistortionTime = 0.0f;
    titlePulse += 0.05f;
    titleDistortionTime += 0.05f;
    float scale = 1.0f + std::sin(titlePulse) * 0.02f;

    // Mise à jour de la taille des textes
    titreTexte.setCharacterSize(60);
    startTexte.setCharacterSize(40);
    paramsTexte.setCharacterSize(40);
    tutorialTexte.setCharacterSize(40);
    exitTexte.setCharacterSize(40);

    // Effet de chromatic aberration pour le titre
    sf::Text titreRed = titreTexte;
    sf::Text titreBlue = titreTexte;
    float distortionAmount = std::sin(titleDistortionTime) * 3.0f;
    titreRed.setPosition(titreTexte.getPosition() + sf::Vector2f(distortionAmount, 0));
    titreBlue.setPosition(titreTexte.getPosition() - sf::Vector2f(distortionAmount, 0));
    titreRed.setFillColor(sf::Color(255, 0, 0, 100));
    titreBlue.setFillColor(sf::Color(0, 0, 255, 100));

    // Effet de glitch pour le titre
    titreTexte.setCharacterSize(60);
    titreTexte.setFillColor(sf::Color(0, 157, 255)); // Couleur cyan/bleu fixe

    // Simple ombre pour la profondeur
    sf::Text titreShadow = titreTexte;
    titreShadow.setPosition(titreTexte.getPosition() + sf::Vector2f(4, 4));
    titreShadow.setFillColor(sf::Color(0, 0, 0, 150));

    // Rendu du titre
    window.draw(titreShadow);
    window.draw(titreTexte);

    window.draw(titreShadow);
    window.draw(titreRed);
    window.draw(titreBlue);
    titreTexte.setScale(scale, scale);
    window.draw(titreTexte);

    // Gestion des boutons du menu avec effets améliorés
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    std::vector<sf::Text*> menuTexts = { &startTexte, &paramsTexte, &tutorialTexte, &exitTexte };
    static std::vector<float> buttonPulses(menuTexts.size(), 0.0f);
    static std::vector<bool> buttonHovered(menuTexts.size(), false);

    // Barres stylisées entre les boutons
    static float barPulse = 0.0f;
    barPulse += 0.05f;

    for (size_t i = 0; i < menuTexts.size() - 1; i++) {
        sf::RectangleShape decorativeLine(sf::Vector2f(400.f, 2.f));
        float yPos = (menuTexts[i]->getPosition().y + menuTexts[i + 1]->getPosition().y) / 2.f;

        decorativeLine.setPosition(
            window.getSize().x / 2.f - 200.f + std::sin(barPulse + i) * 10.f,
            yPos
        );

        float gradientPos = std::fmod(barPulse + i * 0.5f, 1.0f);
        sf::Color lineColor(0, 157, 255, static_cast<sf::Uint8>(100 + 50 * std::sin(barPulse + i)));
        decorativeLine.setFillColor(lineColor);

        window.draw(decorativeLine);

        // Points décoratifs aux extrémités
        sf::CircleShape endPoint(2.f);
        endPoint.setFillColor(lineColor);
        endPoint.setPosition(decorativeLine.getPosition().x - 2.f, yPos - 2.f);
        window.draw(endPoint);
        endPoint.setPosition(
            decorativeLine.getPosition().x + decorativeLine.getSize().x - 2.f,
            yPos - 2.f
        );
        window.draw(endPoint);
    }

    // Décorations latérales
    float sideOffset = 80.f;
    drawSideDecoration(sideOffset, window.getSize().y / 2.f - 300.f, true);
    drawSideDecoration(window.getSize().x - sideOffset, window.getSize().y / 2.f - 300.f, false);
    // Rendu des boutons avec effets de survol
    for (size_t i = 0; i < menuTexts.size(); i++) {
        sf::Text* text = menuTexts[i];
        bool isHovered = text->getGlobalBounds().contains(mousePos.x, mousePos.y);

        buttonPulses[i] += isHovered ? 0.1f : -0.1f;
        buttonPulses[i] = std::max(0.0f, std::min(1.0f, buttonPulses[i]));
        float hoverScale = 1.0f + buttonPulses[i] * 0.1f;
        text->setScale(hoverScale, hoverScale);

        if (isHovered) {
            text->setFillColor(sf::Color(0, 255, 255));

            // Particules autour du bouton survolé
            if (rand() % 3 == 0) {
                for (int j = 0; j < 2; j++) {
                    sf::CircleShape sparkle(1.f);
                    sparkle.setPosition(
                        text->getGlobalBounds().left + rand() % static_cast<int>(text->getGlobalBounds().width),
                        text->getGlobalBounds().top + rand() % static_cast<int>(text->getGlobalBounds().height)
                    );
                    sparkle.setFillColor(sf::Color(0, 255, 255, 150));
                    window.draw(sparkle);
                }
            }
        }
        else {
            text->setFillColor(sf::Color::White);
        }

        // Ombre du texte
        sf::Text shadowText = *text;
        shadowText.setPosition(text->getPosition() + sf::Vector2f(2, 2));
        shadowText.setFillColor(sf::Color(0, 0, 0, 100));
        window.draw(shadowText);
        window.draw(*text);
    }

    // Décorations des coins
    for (int i = 0; i < 2; i++) {
        float xPos = i == 0 ? 0.f : window.getSize().x - 200.f;
        sf::RectangleShape cornerDeco(sf::Vector2f(200.f, 100.f));
        cornerDeco.setPosition(xPos, 0);
        cornerDeco.setFillColor(sf::Color(0, 0, 0, 0));
        cornerDeco.setOutlineColor(sf::Color(0, 157, 255, 70));
        cornerDeco.setOutlineThickness(1.f);
        window.draw(cornerDeco);

        // Version en bas
        cornerDeco.setPosition(xPos, window.getSize().y - 100.f);
        window.draw(cornerDeco);
    }

    // Signature avec effets
    static float signaturePulse = 0.0f;
    signaturePulse += 0.03f;

    sf::Text signature;
    signature.setFont(font);
    signature.setString("Created by Darwizzyy");
    signature.setCharacterSize(24);
    signature.setPosition(
        window.getSize().x - signature.getLocalBounds().width - 30.f,
        window.getSize().y - signature.getLocalBounds().height - 20.f
    );

    float signatureAlpha = 128 + 127 * std::sin(signaturePulse);
    signature.setFillColor(sf::Color(0, 157, 255, static_cast<sf::Uint8>(signatureAlpha)));

    // Cadre décoratif pour la signature
    sf::RectangleShape signatureFrame;
    signatureFrame.setSize(sf::Vector2f(
        signature.getLocalBounds().width + 40.f,
        signature.getLocalBounds().height + 20.f
    ));
    signatureFrame.setPosition(
        signature.getPosition().x - 20.f,
        signature.getPosition().y - 10.f
    );
    signatureFrame.setFillColor(sf::Color(0, 0, 0, 50));
    signatureFrame.setOutlineColor(sf::Color(0, 157, 255, static_cast<sf::Uint8>(signatureAlpha)));
    signatureFrame.setOutlineThickness(1.f);

    window.draw(signatureFrame);
    window.draw(signature);

    // Effets finaux
    // Effet de glitch aléatoire
    if (rand() % 200 == 0) {
        sf::RectangleShape glitchLine(sf::Vector2f(window.getSize().x, rand() % 5 + 1));
        glitchLine.setPosition(0, rand() % window.getSize().y);
        glitchLine.setFillColor(sf::Color(255, 255, 255, 50));
        window.draw(glitchLine);
    }

    // Scan-lines
    for (int y = 0; y < window.getSize().y; y += 4) {
        sf::RectangleShape scanLine(sf::Vector2f(window.getSize().x, 1));
        scanLine.setPosition(0, y);
        scanLine.setFillColor(sf::Color(255, 255, 255, 3));
        window.draw(scanLine);
    }

    // Effet de vignette dynamique
    static float screenDistortionTime = 0.0f;
    screenDistortionTime += 0.01f;
    sf::RectangleShape vignetteCorners[4];
    for (int i = 0; i < 4; i++) {
        vignetteCorners[i].setSize(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f));
        float alpha = 100 + 50 * std::sin(screenDistortionTime);
        vignetteCorners[i].setFillColor(sf::Color(0, 0, 20, static_cast<sf::Uint8>(alpha)));
    }

    vignetteCorners[0].setPosition(0, 0);
    vignetteCorners[1].setPosition(window.getSize().x / 2.f, 0);
    vignetteCorners[2].setPosition(0, window.getSize().y / 2.f);
    vignetteCorners[3].setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);

    for (auto& corner : vignetteCorners) {
        window.draw(corner);
    }

    window.display();
}
void SFMLInterface::afficherGrille(const Grille& grille, bool enPause) {
    window.clear(sf::Color(50, 50, 50));

    int hauteurGrille = window.getSize().y - BANDE_NOIRE_HAUTEUR;

    // Dessiner la grille
    for (int i = 0; i < grille.getNbLignes(); ++i) {
        for (int j = 0; j < grille.getNbColonnes(); ++j) {
            if (i * tailleCellule < hauteurGrille) {
                sf::VertexArray quad(sf::Quads, 4);
                float x = static_cast<float>(j * tailleCellule);
                float y = static_cast<float>(i * tailleCellule);
                float size = static_cast<float>(tailleCellule - 1);

                if (grille.getCellule(i, j).estVivante()) {
                    switch (currentTheme) {
                    case ColorTheme::BLUE:
                        quad[0].color = sf::Color(0, 200, 255);   // Bleu vif
                        quad[1].color = sf::Color(0, 255, 255);   // Bleu clair
                        quad[2].color = sf::Color(0, 255, 255);
                        quad[3].color = sf::Color(0, 200, 255);
                        break;
                    case ColorTheme::GREEN:
                        quad[0].color = sf::Color(0, 255, 0);   // Vert vif
                        quad[1].color = sf::Color(0, 255, 50);   // Vert clair
                        quad[2].color = sf::Color(0, 255, 50);
                        quad[3].color = sf::Color(0, 255, 0);
                        break;
                    case ColorTheme::RED:
                        quad[0].color = sf::Color(255, 0, 0);   // Rouge vif
                        quad[1].color = sf::Color(255, 0, 30);   // Rouge clair
                        quad[2].color = sf::Color(255, 0, 30);
                        quad[3].color = sf::Color(255, 0, 0);
                        break;
                    }
                }
                else {
                    // Cellule morte : même dégradé pour tous les thèmes
                    quad[0].color = sf::Color(11, 13, 14);  // Gris sombre
                    quad[1].color = sf::Color(20, 16, 20);  // Gris-noir
                    quad[2].color = sf::Color(20, 16, 20);
                    quad[3].color = sf::Color(11, 13, 14);
                }

                quad[0].position = sf::Vector2f(x, y);
                quad[1].position = sf::Vector2f(x + size, y);
                quad[2].position = sf::Vector2f(x + size, y + size);
                quad[3].position = sf::Vector2f(x, y + size);

                window.draw(quad);
            }
        }
    }

    // Calcul de la population
    int population = 0;
    for (int i = 0; i < grille.getNbLignes(); ++i) {
        for (int j = 0; j < grille.getNbColonnes(); ++j) {
            if (grille.getCellule(i, j).estVivante()) {
                population++;
            }
        }
    }
    populationTexte.setString("Population: " + std::to_string(population));
    generationTexte.setString("Nombre d'iterations: " + std::to_string(nombreMisesAJour));

    // Dessiner la bande noire en bas
    sf::RectangleShape bandeNoire(sf::Vector2f(window.getSize().x, BANDE_NOIRE_HAUTEUR));
    bandeNoire.setPosition(0, window.getSize().y - BANDE_NOIRE_HAUTEUR);
    bandeNoire.setFillColor(sf::Color(11, 13, 30));
    window.draw(bandeNoire);

    // Dessiner tous les éléments de l'interface
    window.draw(oscillateurSprite);
    window.draw(planeurSprite);
    window.draw(canonSprite);
    window.draw(resetSprite);
    window.draw(oscillateurNom);
    window.draw(planeurNom);
    window.draw(canonNom);
    window.draw(oscillateurTexte);
    window.draw(planeurTexte);
    window.draw(canonTexte);
    window.draw(zoomInSprite);
    window.draw(zoomOutSprite);
    window.draw(undoSprite);
    window.draw(redoSprite);
    window.draw(volumeBar);
    window.draw(volumeSlider);
    window.draw(isMuted ? muteSprite : soundSprite);
    window.draw(speedBar);
    window.draw(speedSlider);
    window.draw(speedSprite);
    window.draw(populationTexte);
    window.draw(generationTexte);
    window.draw(enPause ? playSprite : pauseSprite);

    window.display();
}

void SFMLInterface::resetGeneration() {
    generation = 0;
}

void SFMLInterface::updateVolumeSlider() {
    float sliderX = volumeBar.getPosition().x + (volume / 100.0f) * volumeBar.getSize().x - volumeSlider.getSize().x / 2;
    float sliderY = volumeBar.getPosition().y - volumeSlider.getSize().y / 2 + volumeBar.getSize().y / 2;
    volumeSlider.setPosition(sliderX, sliderY);
}

void SFMLInterface::updateSpeedSlider() {
    float sliderX = speedBar.getPosition().x + (currentSpeed / 100.0f) * speedBar.getSize().x - speedSlider.getSize().x / 2;
    float sliderY = speedBar.getPosition().y - speedSlider.getSize().y / 2 + speedBar.getSize().y / 2;
    speedSlider.setPosition(sliderX, sliderY);
}

void SFMLInterface::handleVolumeControl(const sf::Vector2i& mousePos) {
    if (volumeBar.getGlobalBounds().contains(mousePos.x, mousePos.y) ||
        volumeSlider.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        float relativeX = mousePos.x - volumeBar.getPosition().x;
        volume = (relativeX / volumeBar.getSize().x) * 100;
        volume = std::max(0.0f, std::min(100.0f, volume));
        menuMusic.setVolume(isMuted ? 0 : volume);
        updateVolumeSlider();
    }
}

void SFMLInterface::handleSpeedControl(const sf::Vector2i& mousePos, int& vitesseSimulation) {
    if (speedBar.getGlobalBounds().contains(mousePos.x, mousePos.y) ||
        speedSlider.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        float relativeX = mousePos.x - speedBar.getPosition().x;
        currentSpeed = (relativeX / speedBar.getSize().x) * 100;
        currentSpeed = std::max(0.0f, std::min(100.0f, currentSpeed));
        vitesseSimulation = 2000 - ((currentSpeed / 100.0f) * 1950);
        updateSpeedSlider();
    }
}
void SFMLInterface::toggleMusic() {
    if (musicPlaying) {
        menuMusic.pause();
        musicPlaying = false;
        isMuted = true;
    }
    else {
        menuMusic.play();
        musicPlaying = true;
        isMuted = false;
    }
}

bool SFMLInterface::estOuverte() const {
    return window.isOpen();
}

void SFMLInterface::zoomIn() {
    if (tailleCellule < 50) {
        tailleCellule += 2;
        celluleShape.setSize(sf::Vector2f(tailleCellule - 1, tailleCellule - 1));
    }
}

void SFMLInterface::zoomOut() {
    if (tailleCellule > 4) {
        tailleCellule -= 2;
        celluleShape.setSize(sf::Vector2f(tailleCellule - 1, tailleCellule - 1));
    }
}

void SFMLInterface::toggleCelluleAvecSouris(Grille& grille, const sf::Vector2i& mousePos) {
    if (mousePos.y >= window.getSize().y - BANDE_NOIRE_HAUTEUR) {
        return;
    }

    int colonne = mousePos.x / tailleCellule;
    int ligne = mousePos.y / tailleCellule;

    if (ligne >= 0 && ligne < grille.getNbLignes() && colonne >= 0 && colonne < grille.getNbColonnes()) {
        sauvegarderEtat(grille);
        Cellule& cellule = grille.getCellule(ligne, colonne);
        cellule.setEtat(!cellule.estVivante());
    }
}

void SFMLInterface::resetGrille(Grille& grille) {
    sauvegarderEtat(grille);
    for (int i = 0; i < grille.getNbLignes(); ++i) {
        for (int j = 0; j < grille.getNbColonnes(); ++j) {
            grille.getCellule(i, j).setEtat(false);
        }
    }
    resetMisesAJour();  // Réinitialiser le compteur lors d'un reset
}

void SFMLInterface::ajouterPattern(Grille& grille, const std::vector<std::pair<int, int>>& coords, int ligneBase, int colonneBase) {
    sauvegarderEtat(grille);
    for (const auto& coord : coords) {
        int ligne = ligneBase + coord.first;
        int colonne = colonneBase + coord.second;
        if (ligne >= 0 && ligne < grille.getNbLignes() &&
            colonne >= 0 && colonne < grille.getNbColonnes()) {
            grille.getCellule(ligne, colonne).setEtat(true);
        }
    }
}

void SFMLInterface::ajouterPlaneur(Grille& grille, int ligneBase, int colonneBase) {
    std::vector<std::pair<int, int>> planeur = {
        {0, 1}, {1, 2}, {2, 0}, {2, 1}, {2, 2}
    };
    ajouterPattern(grille, planeur, ligneBase, colonneBase);
}

void SFMLInterface::ajouterCanon(Grille& grille, int ligneBase, int colonneBase) {
    std::vector<std::pair<int, int>> canon = {
        {0, 24},
        {1, 22}, {1, 24},
        {2, 12}, {2, 13}, {2, 20}, {2, 21}, {2, 34}, {2, 35},
        {3, 11}, {3, 15}, {3, 20}, {3, 21}, {3, 34}, {3, 35},
        {4, 0}, {4, 1}, {4, 10}, {4, 16}, {4, 20}, {4, 21},
        {5, 0}, {5, 1}, {5, 10}, {5, 14}, {5, 16}, {5, 17}, {5, 22}, {5, 24},
        {6, 10}, {6, 16}, {6, 24},
        {7, 11}, {7, 15},
        {8, 12}, {8, 13}
    };
    ajouterPattern(grille, canon, ligneBase, colonneBase);
}
void SFMLInterface::ajouterOscillateur(Grille& grille, int ligneBase, int colonneBase) {
    std::vector<std::pair<int, int>> oscillateur = {
        {0, 1}, {1, 1}, {2, 1}
    };
    ajouterPattern(grille, oscillateur, ligneBase, colonneBase);
}

void SFMLInterface::sauvegarderEtat(const Grille& grille) {
    undoStack.push(captureEtatGrille(grille));
    while (!redoStack.empty()) {
        redoStack.pop();
    }
}

void SFMLInterface::undo(Grille& grille) {
    if (!undoStack.empty()) {
        redoStack.push(captureEtatGrille(grille));
        auto previousState = undoStack.top();
        undoStack.pop();
        appliquerEtatGrille(grille, previousState);
    }
}

void SFMLInterface::redo(Grille& grille) {
    if (!redoStack.empty()) {
        undoStack.push(captureEtatGrille(grille));
        auto nextState = redoStack.top();
        redoStack.pop();
        appliquerEtatGrille(grille, nextState);
    }
}

std::vector<std::vector<bool>> SFMLInterface::captureEtatGrille(const Grille& grille) {
    std::vector<std::vector<bool>> etat(grille.getNbLignes(),
        std::vector<bool>(grille.getNbColonnes()));

    for (int i = 0; i < grille.getNbLignes(); ++i) {
        for (int j = 0; j < grille.getNbColonnes(); ++j) {
            etat[i][j] = grille.getCellule(i, j).estVivante();
        }
    }
    return etat;
}

void SFMLInterface::appliquerEtatGrille(Grille& grille, const std::vector<std::vector<bool>>& etat) {
    for (int i = 0; i < grille.getNbLignes(); ++i) {
        for (int j = 0; j < grille.getNbColonnes(); ++j) {
            grille.getCellule(i, j).setEtat(etat[i][j]);
        }
    }
}
void SFMLInterface::afficherTutorial() {
    window.clear(sf::Color(11, 13, 30));

    float centreX = window.getSize().x / 2;
    float startY = 100.0f;
    float spacing = 40.0f;

    std::vector<std::pair<std::string, std::string>> controls = {
        {"Souris gauche", "Dessiner/Effacer des cellules"},
        {"Espace", "Pause/Reprendre la simulation"},
        {"R", "Réinitialiser la grille"},
        {"P", "Placer un planeur à la position du curseur"},
        {"O", "Placer un oscillateur à la position du curseur"},
        {"C", "Placer un canon à la position du curseur"},
        {"Ctrl + Z", "Annuler la dernière action"},
        {"Ctrl + Y", "Rétablir la dernière action"},
        {"M", "Activer/Désactiver la musique"},
        {"Flèches gauche/droite", "Ajuster la vitesse"},
        {"Echap", "Retourner au menu"}
    };

    // Titre
    sf::Text titreTexte;
    titreTexte.setFont(font);
    titreTexte.setString("TUTORIEL");
    titreTexte.setCharacterSize(50);
    titreTexte.setFillColor(sf::Color::White);
    titreTexte.setPosition(
        centreX - titreTexte.getLocalBounds().width / 2,
        startY - 50
    );
    window.draw(titreTexte);

    // Afficher les contrôles
    for (size_t i = 0; i < controls.size(); i++) {
        // Touche
        sf::Text keyText;
        keyText.setFont(font);
        keyText.setString(controls[i].first);
        keyText.setCharacterSize(25);
        keyText.setFillColor(sf::Color(0, 157, 255));
        keyText.setPosition(
            centreX - 300,
            startY + i * spacing
        );

        // Description
        sf::Text descText;
        descText.setFont(font);
        descText.setString(controls[i].second);
        descText.setCharacterSize(25);
        descText.setFillColor(sf::Color::White);
        descText.setPosition(
            centreX - 50,
            startY + i * spacing
        );

        window.draw(keyText);
        window.draw(descText);
    }

    // Bouton retour
    sf::Text retourTexte;
    retourTexte.setFont(font);
    retourTexte.setString("RETOUR");
    retourTexte.setCharacterSize(30);
    retourTexte.setFillColor(sf::Color::White);
    retourTexte.setPosition(
        centreX - retourTexte.getLocalBounds().width / 2,
        startY + controls.size() * spacing + 50
    );

    // Effet de survol pour le bouton retour
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (retourTexte.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        retourTexte.setFillColor(sf::Color(0, 255, 255));
    }

    window.draw(retourTexte);
    window.display();
}
void SFMLInterface::attendreEvenements(int& vitesseSimulation, bool& enPause, Grille& grille) {
    static bool isDraggingVolume = false;
    static bool isDraggingSpeed = false;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        if (isDraggingSpeed || speedBar.getGlobalBounds().contains(mousePos.x, mousePos.y) ||
            speedSlider.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            isDraggingSpeed = true;
            handleSpeedControl(mousePos, vitesseSimulation);
        }
        else if (isDraggingVolume || volumeBar.getGlobalBounds().contains(mousePos.x, mousePos.y) ||
            volumeSlider.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            isDraggingVolume = true;
            handleVolumeControl(mousePos);
        }
        else if (!enMenu && !enThemeMenu && estEnTrainDeModifier) {
            if (!zoomInSprite.getGlobalBounds().contains(mousePos.x, mousePos.y) &&
                !zoomOutSprite.getGlobalBounds().contains(mousePos.x, mousePos.y) &&
                !undoSprite.getGlobalBounds().contains(mousePos.x, mousePos.y) &&
                !redoSprite.getGlobalBounds().contains(mousePos.x, mousePos.y) &&
                !pauseSprite.getGlobalBounds().contains(mousePos.x, mousePos.y) &&
                !playSprite.getGlobalBounds().contains(mousePos.x, mousePos.y) &&
                !resetSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {

                int colonne = mousePos.x / tailleCellule;
                int ligne = mousePos.y / tailleCellule;
                sf::Vector2i celluleActuelle(colonne, ligne);

                if (celluleActuelle != derniereCelluleModifiee) {
                    toggleCelluleAvecSouris(grille, mousePos);
                    derniereCelluleModifiee = celluleActuelle;
                }
            }
        }
    }
    else {
        isDraggingSpeed = false;
        isDraggingVolume = false;
    }

    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            if (enMenu && !enThemeMenu) {
                if (startTexte.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    enMenu = false;
                    enPause = true;
                }
                else if (paramsTexte.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    enThemeMenu = true;
                }
                else if (exitTexte.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    window.close();
                }
            }
            else if (enThemeMenu) {
                float centreX = window.getSize().x / 2;
                float startY = window.getSize().y / 3;
                float spacing = 80.0f;

                // Vérifier les clics sur les options de musique
                for (size_t i = 0; i < musicNames.size(); i++) {
                    sf::Text musicOption;
                    musicOption.setFont(font);
                    musicOption.setString(musicNames[i]);
                    musicOption.setCharacterSize(30);
                    musicOption.setPosition(
                        centreX - musicOption.getLocalBounds().width / 2,
                        startY + i * spacing
                    );

                    if (musicOption.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        selectedMusic = i;
                        menuMusic.stop();
                        if (menuMusic.openFromFile(musicPaths[i])) {
                            menuMusic.setLoop(true);
                            menuMusic.setVolume(volume);
                            if (!isMuted) {
                                menuMusic.play();
                            }
                        }
                    }
                }

                // Vérifier les clics sur les options de thème
                float themeStartY = startY + (musicNames.size() + 1) * spacing;
                for (size_t i = 0; i < themeNames.size(); i++) {
                    sf::Text themeOption;
                    themeOption.setFont(font);
                    themeOption.setString(themeNames[i]);
                    themeOption.setCharacterSize(30);
                    themeOption.setPosition(
                        centreX - themeOption.getLocalBounds().width / 2,
                        themeStartY + i * spacing
                    );

                    if (themeOption.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        currentTheme = static_cast<ColorTheme>(i);
                    }
                }

                // Vérifier le clic sur le bouton retour
                sf::Text retourTexte;
                retourTexte.setFont(font);
                retourTexte.setString("RETOUR");
                retourTexte.setCharacterSize(30);
                retourTexte.setPosition(
                    centreX - retourTexte.getLocalBounds().width / 2,
                    themeStartY + themeNames.size() * spacing + 50
                );

                if (retourTexte.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    enThemeMenu = false;
                }
            }
            else {
                if (resetSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    resetGrille(grille);
                }
                else if (zoomInSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    zoomIn();
                }
                else if (zoomOutSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    zoomOut();
                }
                else if (undoSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    undo(grille);
                }
                else if (redoSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    redo(grille);
                }
                else if (soundSprite.getGlobalBounds().contains(mousePos.x, mousePos.y) ||
                    muteSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    toggleMusic();
                }
                else if (pauseSprite.getGlobalBounds().contains(mousePos.x, mousePos.y) ||
                    playSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    enPause = !enPause;
                }
                else {
                    estEnTrainDeModifier = true;
                    derniereCelluleModifiee = sf::Vector2i(mousePos.x / tailleCellule, mousePos.y / tailleCellule);
                    toggleCelluleAvecSouris(grille, mousePos);
                }
            }
        }
        else if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                estEnTrainDeModifier = false;
                derniereCelluleModifiee = sf::Vector2i(-1, -1);
            }
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::M) {
                toggleMusic();
            }
            if (event.key.control) {
                if (event.key.code == sf::Keyboard::Z) {
                    undo(grille);
                }
                else if (event.key.code == sf::Keyboard::Y) {
                    redo(grille);
                }
            }

            if (!enMenu && !enThemeMenu) {
                switch (event.key.code) {
                case sf::Keyboard::R:
                    resetGrille(grille);
                    break;
                case sf::Keyboard::Left:
                    currentSpeed = std::max(0.0f, currentSpeed - 5.0f);
                    vitesseSimulation = 2000 - ((currentSpeed / 100.0f) * 1950);
                    updateSpeedSlider();
                    break;
                case sf::Keyboard::Right:
                    currentSpeed = std::min(100.0f, currentSpeed + 5.0f);
                    vitesseSimulation = 2000 - ((currentSpeed / 100.0f) * 1950);
                    updateSpeedSlider();
                    break;
                case sf::Keyboard::P:
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    int ligne = mousePos.y / tailleCellule;
                    int colonne = mousePos.x / tailleCellule;
                    ajouterPlaneur(grille, ligne, colonne);
                }
                break;
                case sf::Keyboard::C:
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    int ligne = mousePos.y / tailleCellule;
                    int colonne = mousePos.x / tailleCellule;
                    ajouterCanon(grille, ligne, colonne);
                }
                break;
                case sf::Keyboard::O:
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    int ligne = mousePos.y / tailleCellule;
                    int colonne = mousePos.x / tailleCellule;
                    ajouterOscillateur(grille, ligne, colonne);
                }
                break;
                case sf::Keyboard::Space:
                    enPause = !enPause;
                    break;
                case sf::Keyboard::Escape:
                    if (!enMenu) {
                        enMenu = true;
                        enPause = true;
                    }
                    break;
                }
            }
        }
    }
}
