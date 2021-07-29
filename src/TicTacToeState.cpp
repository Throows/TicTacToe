#include "TicTacToeState.h"

void TicTacToeState::initVariables()
{
	this->playerTurn = true;
}

void TicTacToeState::initBackground()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/TicTacToeBC.png"))
	{
		throw ("Error : cannot load background (MenuState)");
	}
	this->background.setTexture(&this->backgroundTexture);
}

void TicTacToeState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Minecraft.ttf"))
	{
		throw("ERROR : Could not load font ! (TIC-TAC-TOE STATE)");
	}

}

void TicTacToeState::initTextures()
{
	if (!this->textures["MENU_FORMS"].loadFromFile("Resources/Images/Forms/TTTMenuForms.png")) {
		throw("ERROR : Could not load Form Textures ! (TIC-TAC-TOE STATE)");
	}

}

void TicTacToeState::initButtons()
{
	
	this->cases["A0"] = new Case(15, 35, 110, 97, &this->textures["MENU_FORMS"], 0, 0);
	this->cases["A1"] = new Case(127, 35, 110, 97, &this->textures["MENU_FORMS"], 0, 1);
	this->cases["A2"] = new Case(239, 35, 110, 97, &this->textures["MENU_FORMS"], 0, 2);
	this->cases["B0"] = new Case(15, 134, 110, 95, &this->textures["MENU_FORMS"], 1, 0);
	this->cases["B1"] = new Case(127, 134, 110, 95, &this->textures["MENU_FORMS"], 1, 1);
	this->cases["B2"] = new Case(239, 134, 110, 95, &this->textures["MENU_FORMS"], 1, 2);
	this->cases["C0"] = new Case(15, 231, 110, 95, &this->textures["MENU_FORMS"], 2, 0);
	this->cases["C1"] = new Case(127, 231, 110, 95, &this->textures["MENU_FORMS"], 2, 1);
	this->cases["C2"] = new Case(239, 231, 110, 95, &this->textures["MENU_FORMS"], 2, 2);

}

TicTacToeState::TicTacToeState(sf::RenderWindow* window, std::stack<GameState*>* states, const unsigned int sign)
	: GameState(window, states), sign(sign), IALevel(3)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initTextures();
	//this->initKeybinds();
	this->initButtons();
}

TicTacToeState::~TicTacToeState()
{
}

void TicTacToeState::updateInputs(const float& dtime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		this->endState();
}

void TicTacToeState::updateButtons()
{
	for (auto& it : this->cases)
		it.second->update(this->mousePosView);

	for (auto& it : this->cases) {

		if (it.second->isPressed() && !it.second->HasRealTexture()) {
			switch (sign){
			case 1:
				it.second->changeTexture(TextureStates::ROUND);
				break;
			case 2:
				it.second->changeTexture(TextureStates::CROSS);
				break;
			}
			this->ticTacToeCoord[it.second->getXCoord()][it.second->getYCoord()] = sign;
			this->playerTurn = false;
		}
	}
	
}

void TicTacToeState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInputs(dt);

	if (playerTurn) {
		this->updateButtons();
	}else {
		this->IALevel = 3;
		IAPlay();
		this->playerTurn = true;
	}
	
	if(winner(this->ticTacToeCoord) != 0) {
		winText.setPosition(
			(this->window->getSize().x /2.f) - (winText.getGlobalBounds().width / 2.f),
			(this->window->getSize().y / 2.f) - (winText.getGlobalBounds().height / 2.f));
		winText.setFont(this->font);
		winText.setCharacterSize(40);
		std::stringstream ss;
		if (winner(this->ticTacToeCoord) == this->sign) {
			ss << "Bravo ! Vous avez gagné !";
			winText.setFillColor(sf::Color::Green);
		}
		else if(winner(this->ticTacToeCoord) == 3) {
			ss << "Tu as eu chaud. Equalité !";
			winText.setFillColor(sf::Color::Blue);
		}
		else {
			ss << "Oh non tu as perdu !";
			winText.setFillColor(sf::Color::Red);
		}
		winText.setString(ss.str());
	}
}

void TicTacToeState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->cases) {
		it.second->render(target);
	}
}

void TicTacToeState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	target->draw(this->background);

	renderButtons(target);

	target->draw(winText);

	/*sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 20);
	mouseText.setFont(this->font);
	mouseText.setFillColor(sf::Color::Black);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);*/
}

void TicTacToeState::IAPlay() {

	TextureStates IATexture = (this->sign == 1) ? TextureStates::CROSS : TextureStates::ROUND;
	int IATextureNb = (this->sign == 1) ? 2 : 1;

	int IATicTacToe[3][3];
	memcpy(IATicTacToe, this->ticTacToeCoord, sizeof IATicTacToe);

	//coutTable("IA TABLE", IATicTacToe);

	int maximum = -10000;
	
	int max_x = 0;
	int max_y = 0;

	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			if (IATicTacToe[x][y] == 0) {
				IATicTacToe[x][y] = IATextureNb;
				int temp = mini_value(IATicTacToe);
				if (temp > maximum) {
					maximum = temp;
					max_x = x;
					max_y = y;
				}
				IATicTacToe[x][y] = 0;
			}
		}
	}

	playThisCase(IATexture, max_x, max_y);

}

int TicTacToeState::mini_value(int coords[3][3]) {

	int min = 10000;
	int IATextureNb = (this->sign == 1) ? 2 : 1;
	this->IALevel--;

	if(this->IALevel == 0 || winner(coords) != 0){
		return evaluate(coords);
	}
	
	for (int x = 0; x < 3; x++){
		for (int y = 0; y < 3; y++)
		{
			if (coords[x][y] == 0) {
				coords[x][y] = this->sign;
				int temp = maxi_value(coords);
				if (temp < min) {
					min = temp;
				}
				coords[x][y] = 0;
			}
		}

	}
	return min;
}

int TicTacToeState::maxi_value(int coords[3][3]) {

	int max = -10000;
	int IATextureNb = (this->sign == 1) ? 2 : 1;
	this->IALevel--;

	if (this->IALevel == 0 || winner(coords) != 0) {
		return evaluate(coords);
	}

	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++)
		{
			if (coords[x][y] == 0) {
				coords[x][y] = IATextureNb;
				int temp = mini_value(coords);
				if (temp > max) {
					max = temp;
				}
				coords[x][y] = 0;
			}
		}
	}
	return max;
}

int TicTacToeState::winner(int coords[3][3])
{
	int Player = 0;
	int IA = 0;
	nb_series(coords, IA, Player, 3);
	int IATextureNb = (this->sign == 1) ? 2 : 1;

	if (IA) return IATextureNb;
	else if (Player) return this->sign;
	else {
		for (int x = 0; x < 3; x++){
			for (int y = 0; y < 3; y++)
			{
				if (coords[x][y] == 0) return 0;
			}
		}
	}

	return 3;
}

int TicTacToeState::evaluate(int coords[3][3])
{
	int nbCases = 0;
	int IATextureNb = (this->sign == 1) ? 2 : 1;

	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++){
			if (coords[x][y] != 0) nbCases++;
		}
	}

	if (winner(coords) != 0) {
		int playerWinner = winner(coords);

		if (playerWinner == IATextureNb) return 1000 - nbCases;
		else if (playerWinner == this->sign) return -1000 + nbCases;
		else return 0;

	}

	int seriesIA = 0;
	int seriesPlayer = 0;

	nb_series(coords, seriesIA, seriesPlayer, 2);

	return seriesIA - seriesPlayer;
}

int TicTacToeState::nb_series(int coords[3][3], int &seriesIA, int &seriesPlayer, int nbCases)
{

	int IATextureNb = (this->sign == 1) ? 2 : 1;

	seriesIA = 0;
	seriesPlayer = 0;
	int CIA = 0;
	int CPlayer = 0;

	//DIAG desc
	for (int i = 0; i < 3; i++) {
		if (coords[i][i] == this->sign) {
			CPlayer++;
			CIA = 0;
			if (CPlayer == nbCases) {
				seriesPlayer++;
			}
		}
		else if (coords[i][i] == IATextureNb) {
			CIA++;
			CPlayer = 0;
			if (CIA == nbCases) {
				seriesIA++;
			}
		}
	}

	CIA = 0;
	CPlayer = 0;

	//DIAG mont
	for (int i = 0; i < 3; i++) {
		if (coords[i][2-i] == this->sign) {
			CPlayer++;
			CIA = 0;
			if (CPlayer == nbCases) {
				seriesPlayer++;
			}
		}
		else if (coords[i][2-i] == IATextureNb) {
			CIA++;
			CPlayer = 0;
			if (CIA == nbCases) {
				seriesIA++;
			}
		}
	}
	CIA = 0;
	CPlayer = 0;

	//ligne
	for (int i = 0; i < 3; i++) {
		CIA = 0;
		CPlayer = 0;
		//HORIZON
		for (int y = 0; y < 3; y++) {
			if (coords[i][y] == this->sign) {
				CPlayer++;
				CIA = 0;
				if (CPlayer == nbCases) {
					seriesPlayer++;
				}
			}
			else if (coords[i][y] == IATextureNb) {
				CIA++;
				CPlayer = 0;
				if (CIA == nbCases) {
					seriesIA++;
				}
			}
		}

		CIA = 0;
		CPlayer = 0;

		for (int y = 0; y < 3; y++) {
			if (coords[y][i] == this->sign) {
				CPlayer++;
				CIA = 0;
				if (CPlayer == nbCases) {
					seriesPlayer++;
				}
			}
			else if (coords[y][i] == IATextureNb) {
				CIA++;
				CPlayer = 0;
				if (CIA == nbCases) {
					seriesIA++;
				}
			}
		}
	}
	return 0;
}

void TicTacToeState::playThisCase(TextureStates textureState, const int xCoord, const int yCoord) {
	
	int textStateNb = (textureState == TextureStates::ROUND) ? 1 : 2;

	for (auto& it : this->cases) {
		if (it.second->getXCoord() == xCoord && it.second->getYCoord() == yCoord) {
			if (!it.second->hasTexture()) {
				it.second->changeTexture(textureState);
				this->ticTacToeCoord[it.second->getXCoord()][it.second->getYCoord()] = textStateNb;
				this->playerTurn = true;
			}
		}
	}

	//coutTable("TICTACTOETABLE", this->ticTacToeCoord);

}

/*void  TicTacToeState::coutTable(std::string name, int coords[3][3]) {
	std::cout << "-------------------" << name << "------------------------\n";
	std::cout << "{ " << coords[0][0] << " , " << coords[0][1] << " , " << coords[0][2] << " }\n";
	std::cout << "{ " << coords[1][0] << " , " << coords[1][1] << " , " << coords[1][2] << " }\n";
	std::cout << "{ " << coords[2][0] << " , " << coords[2][1] << " , " << coords[2][2] << " }\n";
	std::cout << "-------------------------------------------\n";
}*/