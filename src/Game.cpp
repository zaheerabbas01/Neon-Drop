#include "Game.h"

// private functions
void Game::initVariables()
{
    this->window = nullptr;

    // game logic
    this->points = 0;
    this->enemySpawnTimerMax = 10.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 5;
    this->mouseHeld = false;
    this->health = 20;
    this->endGame = false;
}

void Game::initWindow()
{
    this->videoMode.size = {1920,1080};
    
    this->window = new sf::RenderWindow(this->videoMode, "Game 1", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(60);
}
void Game::initEnemy()
{
    this->enemy.setSize({100.f,100.f});
    this->enemy.setFillColor(sf::Color::Cyan);
    this->enemy.setOutlineColor(sf::Color::Blue);
    this->enemy.setOutlineThickness(10.f);
    this->enemy.setPosition({300.f,300.f});
}
void Game::initFonts()
{
    if (!this->font.openFromFile("assets/Roboto-VariableFont_wdth,wght.ttf"))
    {
        throw "ERROR:: INITFONTS:: FAILED TO LOAD FONT";
    }
}

void Game::initText()
{
    this->uiText.setCharacterSize(40);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setString("None");
}
void Game::restartGame()
{
    this->endGame = false;
    this->points = 0;
    this->health = 20;
    this->enemies.clear();
    this->uiText.setPosition({0,0});
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->initText();
}


// constructors /destructors
Game::Game():uiText(font)
{
    this->initVariables();
    this->initWindow();
    this->initEnemy();
    this->initFonts();
    this->initText();
}

Game::~Game()
{
    delete this->window;
}

// Accessors
const bool Game::running() const
{
    return this->window->isOpen();
}

// const bool Game::getEndgame() const
// {
//     return this->endGame;
// }

// functions
void Game::pollEvenets()
{
    while (const std::optional event = this->window->pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            this->window->close();
        }
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
            {
                this->window->close();
            }
            else if (keyPressed->scancode == sf::Keyboard::Scancode::Enter)
            {
                this->restartGame();

            }
        }
    }
    
}


void Game::spawnEnemy()
{
    /*
     @return void
     spawns enemies and set their colors and positions.
     - set a random position
     - sets a random color
     - adds enemy to the vector
    */

    this->enemy.setPosition({
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)), 0.f});
    
    // randomie enemy type (0-4)
    int type = rand() % 5;

    switch (type)
    {
    case 0:
        this->enemy.setSize({20.f,20.f});
        this->enemy.setFillColor(sf::Color::Magenta);
        break;
    case 1:
        this->enemy.setSize({40.f,20.f});
        this->enemy.setFillColor(sf::Color::Red);
        break;
    case 2:
        this->enemy.setSize({50.f,50.f});
        this->enemy.setFillColor(sf::Color::Blue);
        this->enemy.setOutlineColor(sf::Color::White);
        break;
    case 3:
        this->enemy.setSize({70.f,70.f});
        this->enemy.setFillColor(sf::Color::Green);
        break;
    case 4:
        this->enemy.setSize({100.f,100.f});
        this->enemy.setFillColor(sf::Color::Yellow);
        break;
    default:
        break;
    }

    // spawn the enemy
    this->enemies.push_back(this->enemy);
}

void Game::updateText()
{
    // loading from sstream
    std::stringstream ss;

    ss << "Points: " << this->points << '\n' 
    << " Health: " << this->health;

    this->uiText.setString(ss.str());
}

void Game::updateMousePos()
{
    // store mouse positions

    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateEnemies()
{
    
    // updating the timer for enemy spwaning
    if (this->enemies.size() < this->maxEnemies)
    {
        if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
        {
            // spawn the enemy and reset the timer
            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        }
        else {
            this->enemySpawnTimer += 1.f;
        }
    }
    
    // moving and updating enemies
    for (int i = 0; i < this->enemies.size(); i++)
    {
        this->enemies[i].move({0.f, 2.f});

        // if enemy goes out of screen delete it
        if (this->enemies[i].getPosition().y > this->window->getSize().y)
        {
            this->enemies.erase(this->enemies.begin() + i);
            this->health -= 5;
        }
    }

    // if clicked upon
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !this->mouseHeld)
    {
        this->mouseHeld = true;
        bool deleted = false;

        for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
        {
            if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
            {
                // Gain points
                if (this->enemies[i].getFillColor() == sf::Color::Magenta)
                    this->points += 10;
                else if (this->enemies[i].getFillColor() == sf::Color::Red)
                    this->points += 5;
                else if (this->enemies[i].getFillColor() == sf::Color::Blue)
                    this->points += 4;
                else if (this->enemies[i].getFillColor() == sf::Color::Green)
                    this->points += 3;
                else
                    this->points += 2;

                deleted = true;
                this->enemies.erase(this->enemies.begin() + i);

            }
        }
    } else {
        this->mouseHeld = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left); 
    }
}

void Game::update()
{
    this->pollEvenets();

    if (this->endGame == false)
    {
        this->updateMousePos();
        
        this->updateText();

        this->updateEnemies();
    }

    if (this->health <= 0)
    {
        this->endGame = true;
    }
    
    
}

void Game::renderText(sf::RenderTarget &target)
{
    target.draw(this->uiText);
}
void Game::renderEnemies(sf::RenderTarget &target)
{
    // rendering all the enemies
    for (auto &e : this->enemies)
    {
        target.draw(e);
    }
}


void Game::render()
{
    this->window->clear();

    if (!this->endGame)
    {
        // draw Objects
        this->renderEnemies(*this->window);
        this->renderText(*this->window);
    } else {
        
        this->uiText.setString("GAME OVER\nYour Score: " + std::to_string(this->points) + "\nPress:\n ESC -- exit\n Enter -- retry");
        this->uiText.setCharacterSize(80);
        this->uiText.setPosition({            
            this->window->getSize().x / 2.f - this->uiText.getGlobalBounds().size.x / 2.f,
            this->window->getSize().y / 2.f - this->uiText.getGlobalBounds().size.y / 2.f}
        );
        this->renderText(*this->window);
    }
    

    this->window->display();
}

