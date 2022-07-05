#include "ship.h"

void ship::spawnShip()
{
	this->speed = 1; //essentially the spped of the bullet
	this->rateMax = 100.f;// minimum interval between two bullets 
	this->rate = this->rateMax;
	// here the traingle object is our main ship
	this->triangle.setPointCount(3);
	this->triangle.setRadius(20.f);
	this->triangle.setPosition(200.f, 500.f);
	this->triangle.setFillColor(sf::Color::White);
	this->maxBulls = 4;
	// max bullets at a given time

	this->passThrough = false; // if the bullet can pass through objects

	this->bullSize.x = 4.f;
	this->bullSize.y = 10.f;
	this->bullColor = sf::Color::Red;
	this->bullPos = this->triangle.getPosition();
	// initial position of bullet is ship's position
}

void ship::updateShip(unsigned x,sf::RenderWindow *win)
{	
	//if (x != 0)
		//this->speed = 3;
	//this->speed = ceil(x / 50.f);
	if(this->triangle.getPosition().y < win->getSize().y && this->triangle.getPosition().x < win->getSize().x){
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			this->triangle.move(this->speed, 0.f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			this->triangle.move(0.f, this->speed);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			this->triangle.move(-this->speed, 0.f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			this->triangle.move(0.f, -this->speed);
		}
	}
	else if(this->triangle.getPosition().y >= win->getSize().y) {
		std::cout << "out of bounds in y\n";
		this->triangle.move(0.f, -10.f);
	}
	else if (this->triangle.getPosition().x >= win->getSize().x) {
		std::cout << "out of bounds in x\n";
		this->triangle.move(-10.f, 0.f);
	}
}

void ship::renderShip(sf::RenderWindow* win)
{
	//function to draw ship on our window
	win->draw(this->triangle);
}
void ship::initBullet()
{
	// initiallising bullet's parameters
	this->bull.setSize(bullSize);
	this->bull.setFillColor(bullColor);
	this->bull.setPosition(this->triangle.getPosition());
	this->bulls.push_back(this->bull);
}

void ship::createBullet()
{
	//creating bullets under provided/given conditions
	if (this->bulls.size() < maxBulls&& sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (this->rate >= this->rateMax)
		{
			this->initBullet();
			this->rate = 0.f;
		}
		else
			this->rate+= 3.f;
	}
}

void ship::setBulletPara()
{
	// function to change bullet parameters acc. to the key pressed
	//sniper
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
		this->speed = 3.f;
		this->rateMax = 80.f;
		this->rate = this->rateMax;
		this->maxBulls = 3;
		this->passThrough = true;
		this->bullSize.x = 4.f;
		this->bullSize.y = 40.f;
		this->bullColor = sf::Color::Red;
	}
	//high firerate
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
		this->speed = 1.5f;
		this->rateMax = 30.f;
		this->rate = this->rateMax;
		this->maxBulls = 5;
		this->passThrough = false;
		this->bullSize.x = 4.f;
		this->bullSize.y = 10.f;
		this->bullColor = sf::Color::Yellow;
	}
}

void ship::updateBullet(sf::RenderWindow* win)
{
	// function to update bullet positions
	for (int i = 0; i < this->bulls.size(); i++) {
		this->bulls[i].move(0.f, -3.f);
		//std::cout <<"bulls size : " << bulls.size() << std::endl;
		if (bulls[i].getPosition().y < win->getSize().y - 600) {
			this->bulls.erase(this->bulls.begin() + i);
			//delete bullets if they cross the window
		}
	}
}

void ship::renderBullet(sf::RenderWindow* win)
{
	// function to draw bullets on our main window
	for (auto& x : this->bulls) {
		win->draw(x);
	}
}

