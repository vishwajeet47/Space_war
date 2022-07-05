
#pragma once //like include but reads files only once
#include"ship.h"

// This class Acts as a game engine
class GameClass : public ship
{
private:

	//Variables
	//Windpow
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;

	//mouse pos 
	
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Fonts and others
	sf::Font font;
	sf::Font font2;
	//text
	sf::Text txt;
	sf::Text txt2;
	//game logic
	unsigned points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;
	bool gameOver;
	std::string name;
	
	sf::Color EnemyColor;
	
	// game objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy; 

	//Private Functions
	void initvariables();
	void initwindow();
	void initEnemies();
	void initFonts();
	void initText();
	void initwindow(sf::RenderWindow* win);
	



public:
	bool Exit;
	//Constructors and destructors
	GameClass();
	GameClass(sf::RenderWindow* win);
	virtual ~GameClass();

	//Accessors
	const bool running() const;
	const bool getgameOver() const;

	//functions

	void spawnEnemy();
	void updateEnemy();
	void renderEnemy();
	void updateText();
	void renderText(sf::RenderWindow* win);

	void updateMousePos();
	void update();
	void render();
	void pollEvent();
	void checkHit();
	void friend friendTochangeBullet(GameClass&g);
	void LevelUpdate();
	void ClearWindow(sf::RenderWindow* win);
	unsigned getPonts();
	
};