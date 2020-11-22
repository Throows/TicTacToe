#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<iostream>
#include<fstream>
#include<sstream>
#include<stack>
#include<map>
#include<vector>

class MovementComponent
{
private:
	float maxVelocity;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	sf::Vector2f deceleration;



public:
	MovementComponent(float maxVelocity);
	virtual ~MovementComponent();

	const sf::Vector2f& getVelocity() const;

	void move(const float dir_x, const float dir_y);
	void update(const float& dt);
};
