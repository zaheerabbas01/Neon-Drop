#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Game
{
private:
    // variables
    //window

    sf::RenderWindow* window;
    sf::VideoMode videoMode;

    // Resources
    sf::Font font;

    // Text
    sf::Text uiText;

    // Game Logic
    unsigned points;
    float enemySpawnTimer;
    float enemySpawnTimerMax;
    int maxEnemies;
    bool mouseHeld;
    int health;
    bool endGame;

    // Game Objects
    std::vector<sf::RectangleShape> enemies;
    sf::RectangleShape enemy;

    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    // private functions
    void initWindow();
    void initVariables();
    void initEnemy();
    void initFonts();
    void initText();
    void restartGame();

public:
    // constructors / destructors
    Game(/* args */);
    virtual ~Game();

    //Accessors
    const bool running() const;
    // const bool getEndgame() const;

    // functions
    void spawnEnemy();
    void pollEvenets();

    void updateText();
    void updateMousePos();
    void updateEnemies();
    void update();

    void renderText(sf::RenderTarget& target);
    void renderEnemies(sf::RenderTarget &target);
    void render();
};
