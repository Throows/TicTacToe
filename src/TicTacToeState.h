#pragma once

#include "GameState.h"

class TicTacToeState
	: public GameState
{
private:

    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;
    std::map<std::string, Case*> cases;
    bool playerTurn;
    int IALevel;
    sf::Text winText;
    unsigned int sign;
    int ticTacToeCoord[3][3] = {            
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };

    void initVariables();
    void initBackground();
    void initFonts();
    void initTextures();
    void initButtons();

    void IAPlay();
    void playThisCase(TextureStates textureState, const int xCoord, const int yCoord);

    int mini_value(int coords[3][3]);
    int maxi_value(int coords[3][3]);

    int winner(int coords[3][3]);
    int nb_series(int coords[3][3], int &seriesIA, int &seriesPlayer, int nbCases);
    int evaluate(int coords[3][3]);

    void coutTable(std::string name, int coords[3][3]);

public:
	TicTacToeState(sf::RenderWindow* window, std::stack<GameState*>* states, const unsigned int sign);
	virtual ~TicTacToeState();

    // Functions
    void updateInputs(const float& dtime);
    void updateButtons();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget* target);
    void render(sf::RenderTarget* target);
};    