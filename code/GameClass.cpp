#include "GameClass.h"
#include "ship.h"
//#include "Hero.h"

//private functions
void GameClass::initvariables()
{
	this->window = nullptr;
    this->gameOver = false;
    //game logic
 
    this->points = 0;
    this->health = 1;
    this->enemySpawnTimerMax = 300.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 8;
    this->mouseHeld = false;
    this->EnemyColor = sf::Color::White;
    this->Exit = false;

}

void GameClass::initwindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 400;

	this->window = new sf::RenderWindow(sf::VideoMode(400, 600), "Game 1", sf::Style::Titlebar | sf::Style::Close);
    
    this->window->setFramerateLimit(144);
}

void GameClass::initwindow(sf::RenderWindow* win) {
    this->window = win;
}

unsigned GameClass::getPonts()
{
    return this->points;
}

void GameClass::initEnemies()
{   
    this->enemy.setPosition(10.f,10.f);
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
    this->enemy.setFillColor(sf::Color::White);
    this->enemy.setOutlineColor(sf::Color::Red);
    this->enemy.setOutlineThickness(3.f);
}


void GameClass::initFonts()
{
    if (!this->font.loadFromFile("Fonts/Minecraft.ttf")){
        std::cout << "Error in INITFONTS : Failed to Load font \n";
    }
    this->font2.loadFromFile("Fonts/Killigs.ttf");
}

void GameClass::initText()
{
    this->txt.setFont(this->font);
    this->txt2.setFont(this->font2);
    this->txt.setCharacterSize(18);
    this->txt2.setCharacterSize(18);
    this->txt.setFillColor(sf::Color::White);
    this->txt2.setFillColor(sf::Color::White);
    this->txt.setString("HELLO");
    this->txt2.setPosition(this->window->getSize().x*0.76 , (this->window->getSize().y) + txt2.getGlobalBounds().height - 600);
    this->txt2.setString("this is for txt2");
}

//constructors and destructors
// default constructor 
GameClass::GameClass()
{
	this->initvariables();
	this->initwindow();
    this->initEnemies();
    this->spawnShip();
    this->initBullet();
    this->initFonts();
    this->initText();
}
// constructor with main window as parameter
GameClass::GameClass(sf::RenderWindow* win)
{
    this->initvariables();
    this->initwindow(win);
    this->initEnemies();
    this->spawnShip();
    this->initBullet();
    this->initFonts();
    this->initText();
}

GameClass::~GameClass()
{
	//delete this->window;
}

const bool GameClass::running() const
{
	return this->window->isOpen();
}

const bool GameClass::getgameOver() const
{
    return this->gameOver;
}

//functions

void GameClass::pollEvent()
{
    while (this->window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->event.key.code == sf::Keyboard::Escape)
                this->window->close();
            break;
        }
    }
}

void GameClass::LevelUpdate()
{
    if (this->points > 100 && this->points <200 ) {
        this->EnemyColor = sf::Color::Cyan;
        this->enemySpawnTimerMax = 200.f;
    }
    if (this->points > 200) {
        this->EnemyColor = sf::Color::Magenta;
        this->enemySpawnTimerMax = 100.f;
    }
}

void GameClass::ClearWindow(sf::RenderWindow* win)
{
    win->clear();
}


void GameClass::spawnEnemy()
{
    //return void
    //spwans enemy ans sets theitr color and pos
    //sets a rand0m pos 
    //sets a random color
    //adds enemy to the vector
    this->enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
        0.f
    );
    this->enemy.setFillColor(EnemyColor);
    //spawn enemy
    this->enemies.push_back(this->enemy);
}
void GameClass::checkHit() {
    bool deleted = false;
    for(size_t j = 0; j < this->bulls.size(); j++)
    {
        deleted = false;
        for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
        {
            if (this->enemies[i].getGlobalBounds().intersects(this->bulls[j].getGlobalBounds()))
            {
                //std::cout << "Hit\n";
                if(!passThrough)
                    deleted = true;
                this->enemies.erase(this->enemies.begin() + i);
                //gain points
                this->points += 10;
                //std::cout << "point = " << this->points << std::endl;
                if (deleted) {
                    this->bulls.erase(this->bulls.begin()+j);
                }
            }
        }
    }
}
void GameClass::updateEnemy()
    //update timer and returns void, wghen the total amount of enemies is smaller than max
    //moves the enemys downwards
    //removes the enemy at the edge of screen
{
    if (this->enemies.size() < this->maxEnemies)
    {
        if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
        {
            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        }
        else
            this->enemySpawnTimer += 3.f;

    }

    //moving and updating the enemies
    for (int i = 0; i < this->enemies.size(); i++)
    {
        bool deleted = false;

        this->enemies[i].move(0.f, 1.f);
        if (this->enemies[i].getPosition().y > this->window->getSize().y) {
            this->enemies.erase(this->enemies.begin() + i);
            this->health--;
        }
    }
        // check if clicked upon

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (this->mouseHeld == false)
            {   
                this->mouseHeld = true;
                bool deleted = false;

                for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
                {

                    if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
                    {
                        deleted = true;
                        this->enemies.erase(this->enemies.begin() + i);
                        //gain points
                        this->points += 10;
                        //std::cout << "point = " << this->points << std::endl;
                    }
                }
            }
        }
        else
        {
            mouseHeld = false;
        }
}


void GameClass::renderEnemy()
{
    for (auto& e : this->enemies)
    {
        this->window->draw(e);
    }
}

void GameClass::updateMousePos()
{
    //updates mouse position
    //relative to window vector 2i


    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void GameClass::update()
{
    this->pollEvent();
    if(this->gameOver == false)
    {
        //update mouse pos
        this->updateText();
        this->LevelUpdate();
        this->updateMousePos();
        this->updateShip(this->points, this->window);
        this->updateEnemy();
        this->createBullet();
        this->updateBullet(this->window);
        this->checkHit();
    }
    if (this->health <= 0) {
        this->gameOver = true;
    }
    
    //std::cout << "mouse pos : " << sf::Mouse::getPosition(*this->window).x << " " << sf::Mouse::getPosition(*this->window).y << std::endl;
}

void GameClass::render()
{
    /*
        @return void

        clear old frame
        render objects
        display frame in window

        render the game objects
    
    */

    this->window->clear(); //clear old frame

    //draw game
    this->renderText(this->window);
    this->renderEnemy();
    this->renderShip(this->window);
    this->renderBullet(this->window);
    this->window->display();
}

void GameClass::updateText()
{
    std::stringstream ss;
    std::stringstream ss2;

    ss << "Points : " << this->points;    
    ss2 << "Health : " << this->health;
    this->txt.setString(ss.str());
    this->txt2.setString(ss2.str());
}

void GameClass::renderText(sf::RenderWindow *win)
{
    win->draw(this->txt);
    win->draw(this->txt2);
}

void friendTochangeBullet(GameClass& g)
{
    g.setBulletPara();
}
