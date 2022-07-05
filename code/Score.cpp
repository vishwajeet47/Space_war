#include "Score.h"

Score::Score(sf::RenderWindow* win)
{
	this->points = 0;
	this->name = "";
	this->Scorewindow = win;
	this->ScoreFont.loadFromFile("Fonts/Minecraft.ttf");
	this->playerName.setFont(this->ScoreFont);
	this->playerName.setFillColor(sf::Color::Red);
	this->playerName.setCharacterSize(20);
	this->playerName.setPosition(sf::Vector2f(100 , 300));
	this->EnterName.setFont(ScoreFont);
	this->EnterName.setString("Enter Name");
	this->EnterName.setFillColor(sf::Color::Green);
	this->EnterName.setCharacterSize(20);
	this->EnterName.setPosition(sf::Vector2f(100, 200));
}

void Score::updateScore()
{
	sf::Event ScoreEvent;
	bool NameEntered = false;
	while (!NameEntered) {
		while (this->Scorewindow->pollEvent(ScoreEvent))
		{
			// to delete a last string char
			if (ScoreEvent.key.code == sf::Keyboard::BackSpace &&this->name.size()>0) {
				this->name.erase(this->name.size() - 1);
				this->playerName.setString(this->name);
			}
			else if (ScoreEvent.type == sf::Event::TextEntered)
			{
				//taking input and simultaneously inserting in string
				this->name += ScoreEvent.text.unicode;
				this->playerName.setString(this->name);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				//checking if the name has been entered
				NameEntered = true;
			}
			this->displayScore();
		}

	}
}

void Score::displayScore()
{
	this->Scorewindow->clear();
	this->Scorewindow->draw(this->playerName);
	this->Scorewindow->draw(this->EnterName);
	this->Scorewindow->display();
}

void Score::setScore(int points)
{	
	this->points = points;
}

void Score::display_In_Terminal()
{
	std::cout << this->name << "\n";
	std::cout << this->points << "\n";
}

std::string Score::getName()
{
	return this->name;
}
