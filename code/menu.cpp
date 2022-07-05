#include "Menu.h"
#include <iostream>

Menu::Menu(sf::RenderWindow* window)
{
	this->MenuWindow = window;
	this->width = (float)MenuWindow->getSize().x;
	this->height = (float)MenuWindow->getSize().y;
	this->choosen = false;
	if (!font.loadFromFile("Fonts/Killigs.ttf"))
	{
		// handle error
		std::cout << "MENU font not loaded\n";
	}
	font2.loadFromFile("Fonts/Minecraft.ttf");
	this->thanks.setFont(font2);
	this->thanks.setFillColor(sf::Color::Green);
	this->thanks.setCharacterSize(20);
	this->thanks.setString("Thanks for playing this game !\n\nDeveloped by Vishwajeet\n\nPress space to Exit");
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Play");
	menu[0].setPosition(sf::Vector2f(width / 2 - 30, height / (total_items + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Leaderboard");
	menu[1].setPosition(sf::Vector2f(width / 2 - 30, height / (total_items + 1) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Exit");
	menu[2].setPosition(sf::Vector2f(width / 2 - 30, height / (total_items + 1) * 3));

	selectedItemIndex = 0;
}


Menu::~Menu()
{
	
}

void Menu::DrawMenu(sf::RenderWindow* window)
{
	for (int i = 0; i < total_items; i++)
	{
		this->MenuWindow->draw(menu[i]);
	}
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < total_items)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::Move() {
	sf::Event MenuEvent;

	while (this->MenuWindow->pollEvent(MenuEvent))
	{
		switch (MenuEvent.type)
		{
		case sf::Event::Closed:
			MenuWindow->close();
			break;
		case sf::Event::KeyPressed:
			if (MenuEvent.key.code == sf::Keyboard::Escape)
				MenuWindow->close();
			else if (MenuEvent.key.code == sf::Keyboard::W)
				this->MoveUp();
			else if (MenuEvent.key.code == sf::Keyboard::S)
				this->MoveDown();
			else if (MenuEvent.key.code == sf::Keyboard::Enter)
				this->choosen = true;
			break;
		}
	}
	this->DrawMenu(this->MenuWindow);
}

const bool Menu::ifChoosen() const
{
	return this->choosen;
}

void Menu::setChoosen(bool a)
{
	this->choosen = a;
}

void Menu::ShowThanks()
{
	
	MenuWindow->clear();
	MenuWindow->draw(this->thanks);
	MenuWindow->display();
}
