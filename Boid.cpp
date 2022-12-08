#pragma once
#include "Boid.h"

//position
Boid::Boid(sf::Vector2f startPos)
{
    position = startPos;
}

//drawing the boids
void Boid::Draw(sf::RenderWindow &window) 
{
    sf::CircleShape shape(10.f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(position);
    window.draw(shape);
}