#include "Button.h"

Button::Button(float x, float y, float width, float height, sf::Font* font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
    this->buttonState = BTN_IDLE;
	this->transparentHover = 255;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));

	this->font = font;
	this->text.setFont(*this->font);

	this->text.setString(text);
	this->text.setFillColor(sf::Color::Black);
	this->text.setCharacterSize(20);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
	);

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->shape.setFillColor(this->idleColor);

}

Button::Button(float x, float y, float width, float height, sf::Texture* texture, sf::IntRect textRect, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
	this->buttonState = BTN_IDLE;

	this->font = nullptr;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setTexture(texture);
	this->shape.setTextureRect(textRect);

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

}

Button::~Button()
{
}

const bool Button::isPressed() const
{
	return this->buttonState == BTN_RELEASED;
}

void Button::update(const sf::Vector2f mousePos)
{
	//this->buttonState = BTN_IDLE;

	//Hover
	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->transparentHover--;
		if (this->transparentHover <= 10) this->transparentHover = 10;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_PRESSED;
		}
		else if (this->buttonState == BTN_PRESSED) {
			this->buttonState = BTN_RELEASED;
		}
		else {
			this->buttonState = BTN_HOVER;
		}
	}
	else {
		this->buttonState = BTN_IDLE;
		this->transparentHover = 255;
	}


	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		break;
	case BTN_HOVER:
		this->shape.setFillColor(sf::Color(this->hoverColor.r, this->hoverColor.g, this->hoverColor.b, this->transparentHover/4));
		break;
	case BTN_PRESSED:
		this->shape.setFillColor(this->activeColor);
		break;
	default:
		this->shape.setFillColor(sf::Color::Red);
		break;
	}
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->text);
}

void Button::setText(std::string text)
{
	this->text.setString(text);
}
