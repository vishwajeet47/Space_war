#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"

class Score {
	private :
		std::string name;
		sf::Text playerName;
		sf::Text EnterName;
		int points;
		sf::RenderWindow* Scorewindow;
		sf::Font ScoreFont;

	public:
		Score(sf::RenderWindow* win);
		void updateScore();
		void displayScore();
		void setScore(int);
		void display_In_Terminal();
		std::string getName();
};