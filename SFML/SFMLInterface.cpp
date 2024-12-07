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
    if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
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

        // Icône de musique
        sf::CircleShape musicIcon(10.f, 3);  // Triangle pour symbole de lecture
        musicIcon.setPosition(
            cadre.getPosition().x + 20,
            cadre.getPosition().y + cadreHeight / 2 - 10
        );
        musicIcon.setFillColor(i == selectedMusic ? sf::Color(0, 157, 255) : sf::Color(150, 150, 150));

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

            // Effet de particules au survol
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
        }

        window.draw(cadre);
        window.draw(musicIcon);
        window.draw(musicOption);
    }

    // Séparateur animé
    float themeStartY = startY + (musicNames.size() + 1) * spacing;

    sf::RectangleShape separator(sf::Vector2f(400.f, 2.f));
    separator.setPosition(centreX - 200.f, themeStartY - spacing / 2);

    // Effet de gradient animé sur le séparateur
    float gradientPos = (std::sin(pulseTimer * 2) + 1.0f) / 2.0f * 400.f;
    sf::Color sepColor(100, 100, 100);
    sf::Color glowColor(0, 157, 255);

    separator.setFillColor(sepColor);
    window.draw(separator);

    sf::RectangleShape separatorGlow(sf::Vector2f(100.f, 2.f));
    separatorGlow.setPosition(centreX - 200.f + gradientPos, themeStartY - spacing / 2);
    separatorGlow.setFillColor(glowColor);
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
        }
        else {
            themeCadre.setOutlineColor(sf::Color(100, 100, 100));
        }

        // Icône du thème
        sf::CircleShape themeIcon(15.f);
        themeIcon.setPosition(
            themeCadre.getPosition().x + 20,
            themeCadre.getPosition().y + cadreHeight / 2 - 15
        );
        themeIcon.setFillColor(themeColor);

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

            // Effet de particules au survol
            if (rand() % 10 == 0) {
                sf::CircleShape hoverParticle;
                hoverParticle.setRadius(1.0f);
                hoverParticle.setPosition(
                    themeCadre.getPosition().x + rand() % static_cast<int>(cadreWidth),
                    themeCadre.getPosition().y + cadreHeight
                );
                hoverParticle.setFillColor(sf::Color(0, 255, 255, 100));
                window.draw(hoverParticle);
            }
        }

        window.draw(themeCadre);
        window.draw(themeIcon);
        window.draw(themeOption);
    }

    // Bouton retour avec effets améliorés
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
    }

    window.draw(retourCadre);
    window.draw(retourTexte);

    // Effet de scan-lines
    for (int y = 0; y < window.getSize().y; y += 4) {
        sf::RectangleShape scanLine(sf::Vector2f(window.getSize().x, 1));
        scanLine.setPosition(0, y);
        scanLine.setFillColor(sf::Color(255, 255, 255, 3));
        window.draw(scanLine);
    }

    window.display();
}

void SFMLInterface::afficherMenu() {
    if (enThemeMenu) {
        afficherThemeMenu();
        return;
    }

    window.clear(sf::Color(11, 13, 30));

    // Afficher le titre
    window.draw(titreTexte);
    window.draw(triskelionSprite);

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    // Gestion du survol pour les textes
    auto gererSurvol = [&](sf::Text& texte) {
        if (texte.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            texte.setFillColor(sf::Color(0, 255, 255));  // Cyan au survol
        }
        else {
            texte.setFillColor(sf::Color::White);  // Blanc par défaut
        }
        };

    // Application du survol sur chaque texte
    gererSurvol(startTexte);
    gererSurvol(paramsTexte);
    gererSurvol(tutorialTexte);
    gererSurvol(exitTexte);

    // Affichage des textes
    window.draw(startTexte);
    window.draw(paramsTexte);
    window.draw(tutorialTexte);
    window.draw(exitTexte);

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