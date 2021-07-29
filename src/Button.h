#pragma once

#include "Case.h"

enum Button_states
{
	BTN_IDLE = 0, 
	BTN_HOVER, 
	BTN_PRESSED,
	BTN_RELEASED
};

class Button
{
private:
	short unsigned buttonState;

	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;
	unsigned int transparentHover;


public:
	Button(float x, float y, float width, float height, sf::Font* font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	Button(float x, float y, float width, float height, sf::Texture* texture, sf::IntRect textRect, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	~Button();

	//Accessors 
	const bool isPressed() const;



	//Functions 
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);
	void setText(std::string text);


};

