#pragma once

#include "MenuState.h"


class Game
{

private:
	//Variables
	sf::RenderWindow* window;
	sf::Event sfEvent;
	std::vector<sf::VideoMode> videoModes;
	sf::ContextSettings windowSettings;
	bool fullscreen;
	sf::Clock clock;
	float dtime;

	std::map<std::string, int> supportedKeys;

	std::stack<GameState*> states;

	//Functions
	void initVariables();
	void initStates();
	void initWindow();
	void initKeys();

public:
	Game();
	virtual ~Game();

	void updateSFMLEvents();
	void updateDTime();
	void update();

	void render();

	void run();
};

