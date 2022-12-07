#pragma once
#include "Boid.h"

Boid::Boid(sf::Vector2f startPos)
{
    position = startPos;
}

void Boid::Draw(sf::RenderWindow &window) {
    sf::CircleShape shape(10.f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(position);
    window.draw(shape);
}