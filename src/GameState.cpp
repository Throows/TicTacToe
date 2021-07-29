#include "GameState.h"

GameState::GameState(sf::RenderWindow* window, std::stack<GameState*>* states)
	: window(window), quit(false)
{
	this->states = states;
}

GameState::~GameState()
{

}

const bool& GameState::getQuit() const
{
	return this->quit;
}

void GameState::endState()
{
	this->quit = true;
}

void GameState::updateMousePositions()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}