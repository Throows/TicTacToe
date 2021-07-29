#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <stack>

enum class TextureStates {
	EMPTY = 0, 
	CROSS,
	ROUND
};

class Case
{
private:
	sf::RectangleShape shape;
	sf::Texture* texture;
	bool pressState;
	TextureStates textureState;
	unsigned int xCoord;
	unsigned int yCoord;

public:
	Case(float x, float y, float width, float height, sf::Texture* texture, const unsigned int xCoord, const unsigned int yCoord);
	~Case();

	//Accessors 
	const bool isPressed() const;
	bool hasTexture();
	const bool HasRealTexture() const;
	int getXCoord();
	int getYCoord();

	//Functions 
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);
	void changeTexture(TextureStates textureState);

};

