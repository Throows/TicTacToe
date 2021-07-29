#pragma once

#include "TicTacToeState.h"

class MenuState
	: public GameState
{
private:
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;

    std::map <std::string, Button*> buttons;

    void initVariables();
    void initBackground();
    void initFonts();
    void initButtons();
    void initTextures();

public:
    MenuState(sf::RenderWindow* window, std::stack<GameState*>* states);
    virtual ~MenuState();

    // Functions
    void updateInputs(const float& dtime);
    void updateButtons();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget* target);
    void render(sf::RenderTarget* target);

};

