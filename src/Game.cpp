#include "Game.h"

void Game::initVariables()
{
	this->window = NULL;
	this->fullscreen = false;
	this->dtime = 0.f; 
}

void Game::initStates()
{
	this->states.push(new MenuState(this->window, &this->states));
}

void Game::initWindow()
{
	std::ifstream ifs("Config/window.ini");

	this->videoModes = sf::VideoMode::getFullscreenModes();


	std::string title = "None";
	sf::VideoMode window_bounds(sf::VideoMode::getDesktopMode());
	bool fullscreen(false);
	unsigned framerate_limit = 120;
	bool vSync_enabled = false;
	unsigned antialiasing_level(0);

	if (ifs.is_open())
	{
		std::getline(ifs, title);
		ifs >> window_bounds.width >> window_bounds.height;
		ifs >> fullscreen;
		ifs >> framerate_limit;
		ifs >> vSync_enabled;
		ifs >> antialiasing_level;
	}

	ifs.close();

	this->fullscreen = fullscreen;
	this->windowSettings.antialiasingLevel = antialiasing_level;
	if (this->fullscreen)
		this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, windowSettings);
	else
		this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, windowSettings);

	this->window->setFramerateLimit(framerate_limit);
	this->window->setVerticalSyncEnabled(vSync_enabled);

	sf::Image icon;
	if (!icon.loadFromFile("Resources/Images/Icons/appIcon.png")) {
		throw("ERROR : Could not load Form Textures ! (TIC-TAC-TOE STATE)");
	}
	this->window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void Game::initKeys()
{
	std::ifstream ifs("Config/supported_keys.ini");

	if (ifs.is_open())
	{
		std::string key("");
		int key_value(0);
		while (ifs >> key >> key_value)
		{
			this->supportedKeys[key] = key_value;
		}
	}
	ifs.close();
}

Game::Game()
{
	this->initWindow();
	this->initKeys();
	this->initStates();
}

Game::~Game()
{
	delete this->window;

	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

void Game::updateSFMLEvents()
{

	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
		{
			this->window->close();
		}
	}
}

void Game::updateDTime()
{
	this->dtime = this->clock.restart().asSeconds();
}

void Game::update()
{
	this->updateSFMLEvents();

	if (!this->states.empty())
	{
		this->states.top()->update(this->dtime);
		if (this->states.top()->getQuit())
		{
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	else
	{
		this->window->close();
	}
}

void Game::render()
{
	this->window->clear();
	//Render objects
	if (!this->states.empty())
		this->states.top()->render(this->window);

	this->window->display();
}

void Game::run()
{

	while (this->window->isOpen())
	{
		this->updateDTime();
		this->update();
		this->render();
	}

}
