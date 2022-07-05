#pragma once
#include "SFML/Graphics.hpp"

#define total_items 3

class Menu
{
public:
	Menu(sf::RenderWindow* window);
	~Menu();

	void DrawMenu(sf::RenderWindow* window);
	void MoveUp();
	void MoveDown();
	void Move();
	int GetPressedItem() { return selectedItemIndex; }
	const bool ifChoosen() const;
	void setChoosen(bool a);
	void ShowThanks();

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Font font2;
	// array of text objects
	sf::Text menu[total_items];
	sf::Text thanks;
	bool choosen;
	sf::RenderWindow* MenuWindow;
	float width;
	float height;

};