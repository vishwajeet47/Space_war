#pragma once
#include<iostream> 

#include<vector>
#include<ctime>

#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "SFML/Window.hpp"
#include <sstream>

class ship {
	protected :
		// ship parameters
		int hp;
		float speed;
		int damage;
		float rate;
		float rateMax;
		float maxBulls;
		bool passThrough;
		sf::Vector2f bullSize;
		sf::Color bullColor;
		sf::Vector2f bullPos;

		// event for ship
		sf::CircleShape triangle;
		sf::RectangleShape bull;
		std::vector<sf::RectangleShape> bulls;
	public : 
		void spawnShip();
		void updateShip(unsigned x, sf::RenderWindow* win);
		void renderShip(sf::RenderWindow* win);
		void updateBullet(sf::RenderWindow* win);
		void renderBullet(sf::RenderWindow* win);
		void initBullet();
		void createBullet();
		void setBulletPara();
};

