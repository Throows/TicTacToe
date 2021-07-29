#pragma once

#include "Button.h"

class GameState
{

public:

protected:
	sf::RenderWindow* window;
	std::map<std::string, int> keybinds;
	std::map<std::string, sf::Texture> textures;
	std::stack<GameState*>* states;
	bool quit;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;


	//virtual void initKeybinds() = 0;

public:
	GameState(sf::RenderWindow* window, std::stack<GameState*>* states);
	virtual ~GameState();

	const bool& getQuit() const;
	void endState();

	virtual void updateMousePositions();
	virtual void updateInputs(const float& dtime) = 0;
	virtual void update(const float& dtime) = 0;
	virtual void render(sf::RenderTarget* target) = 0;  // remove Nullptr

};

