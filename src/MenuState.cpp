#include "MenuState.h"

MenuState::MenuState(sf::RenderWindow* window, std::stack<GameState*>* states)
	: GameState(window, states)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initTextures();
	//this->initKeybinds();
	this->initButtons();
}

MenuState::~MenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); it++)
	{
		delete it->second;
	}
}

void MenuState::initVariables()
{

}

void MenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/8-BIT WONDER.TTF"))
	{
		throw("ERROR : Could not load font ! (MenuState)");
	}
}


void MenuState::initButtons()
{
	//this->buttons["CIRCLE"] = new Button(50, 120, 100, 100, &this->font, "O", sf::Color(255, 150, 0, 0), sf::Color(255, 200, 0, 255), sf::Color::White);
	this->buttons["CIRCLE"] = new Button(80, 120, 100, 100, &this->textures["MENU_FORMS"], sf::IntRect(0, 0, 100, 100), sf::Color::Blue, sf::Color::White, sf::Color::Black);
	this->buttons["CROSS"] = new Button(280, 120, 100, 100, &this->textures["MENU_FORMS"], sf::IntRect(100, 0, 100, 100), sf::Color::Red, sf::Color::White, sf::Color::Black);
	this->buttons["EXIT"] = new Button(150, 270, 200, 60, &this->font, "QUITTER", sf::Color(255, 150, 0, 0), sf::Color(255, 255, 255, 50), sf::Color::White);
}

void MenuState::initTextures()
{
	if (!this->textures["MENU_FORMS"].loadFromFile("Resources/Images/Forms/TTTMenuForms.png")) {
		throw("ERROR : Could not load Form Textures ! (TIC-TAC-TOE STATE)");
	}
}

void MenuState::initBackground()
{

	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/MenuBackground.png"))
	{
		throw ("Error : cannot load background (MenuState)");
	}
	this->background.setTexture(&this->backgroundTexture);

}

void MenuState::updateInputs(const float& dtime)
{

}

void MenuState::updateButtons()
{

	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	if (this->buttons["CIRCLE"]->isPressed())
	{
		this->states->push(new TicTacToeState(this->window, this->states, 1));
	}

	if (this->buttons["CROSS"]->isPressed())
	{
		this->states->push(new TicTacToeState(this->window, this->states, 2));
	}
	if (this->buttons["EXIT"]->isPressed())
	{
		this->endState();
	}

}

void MenuState::update(const float& dtime)
{
	this->updateMousePositions();
	this->updateInputs(dtime);
	this->updateButtons();
}

void MenuState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void MenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	target->draw(this->background);

	this->renderButtons(target);

	/*sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 20);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText); */
}


