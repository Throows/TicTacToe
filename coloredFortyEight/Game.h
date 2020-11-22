#pragma once

#include "MainMenuState.h"

class Game
{

private:
	//Variables
	sf::RenderWindow *window; 
	sf::Event sfEvent;
	std::vector<sf::VideoMode> videoModes;
	sf::ContextSettings windowSettings;
	bool fullscreen;
	sf::Clock clock;
	float dt;

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

	//Functions
	void initVariables();
	void initWindow();
	void initStates();
	void initKeys();

public:
	Game();
	virtual ~Game();

	//Functions
	void endApplication();

	void updateSFMLEvents();
	void updateDt();
	void update();
	
	void render();

	void run();
};

