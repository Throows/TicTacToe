#include "Case.h"

Case::Case(float x, float y, float width, float height, sf::Texture* texture, unsigned int xCoord, unsigned int yCoord)
{
	this->texture = texture;
	this->xCoord = xCoord;
	this->yCoord = yCoord;
	this->textureState = TextureStates::EMPTY;
	this->pressState = false;
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));

	this->shape.setFillColor(sf::Color::White);

}

Case::~Case()
{
}

const bool Case::isPressed() const
{
    return this->pressState;
}

bool Case::hasTexture()
{
	return this->textureState != TextureStates::EMPTY;
}

const bool Case::HasRealTexture() const
{
	return this->shape.getTexture() != nullptr;
}

int Case::getXCoord() {
	return this->xCoord;
}

int Case::getYCoord() {
	return this->yCoord;
}

void Case::update(const sf::Vector2f mousePos)
{
	this->pressState = false;

	
	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			this->pressState = true;
	}

	switch (this->textureState) {
		case TextureStates::CROSS:
			this->shape.setTextureRect(sf::IntRect(100, 0, 100, 100));
			this->shape.setFillColor(sf::Color::Red);
			this->shape.setTexture(this->texture);
			break;
		case TextureStates::ROUND:
			this->shape.setTextureRect(sf::IntRect(0, 0, 100, 100));
			this->shape.setFillColor(sf::Color::Blue);
			this->shape.setTexture(this->texture);
			break;
		default:
			this->shape.setFillColor(sf::Color::White);
			this->shape.setTexture(nullptr);
			break;
		}
}

void Case::render(sf::RenderTarget* target)
{
	target->draw(shape);
}

void Case::changeTexture(TextureStates textureState)
{
	this->textureState = textureState;
}
