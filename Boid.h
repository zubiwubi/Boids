#pragma once
#include <SFML/Graphics.hpp>

class Boid
{
public:
    sf::Vector2f position;
    sf::Vector2f velocity;
    Boid(sf::Vector2f startPos);

    void Draw(sf::RenderWindow &window);
};