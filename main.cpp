#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Boid.h"

using namespace std;

vector<Boid*> boidList;
int numberOfBoids = 20;


sf::Vector2f rule1(Boid *bJ)
{

    sf::Vector2f pcJ;

    for (auto b : boidList)
    {
        if (b != bJ)
        {
            pcJ = pcJ + b->position;
        }
    }

    int N = boidList.size();
    pcJ = sf::Vector2f(pcJ.x / N - 1, pcJ.y / N - 1);

    pcJ = pcJ - bJ->position;

    pcJ = sf::Vector2f(pcJ.x / 100, pcJ.y / 100); // tweak 100

    return pcJ;

}

sf::Vector2f rule2(Boid *bJ) {

    sf::Vector2f c;

    for (auto b : boidList)
    {
        if (b != bJ)
        {
            float magnitude = sqrt(b->position.x * bJ->position.x + b->position.x * bJ->position.x);
            if(magnitude < 100)
            {
                c = c - (b->position - bJ->position);
            }
        }
    }

    return c; // deel door iets
}

sf::Vector2f rule3(Boid *bJ) {

    sf::Vector2f pvJ;

        for (auto b : boidList)
        {
            if (b != bJ)
            {
                pvJ = b->velocity;
            }
        }

        int N = boidList.size();

 
        pvJ = sf::Vector2f(pvJ.x / N - 1, pvJ.y / N - 1);

        pvJ = pvJ - bJ->velocity;
        pvJ = sf::Vector2f(pvJ.x / 8, pvJ.y / 8);// tweak 8
        return pvJ;

}

void limit_velocity(Boid *b)
{
    int vlim = 150; // tweak speed
    sf::Vector2f v;

    if( sqrt(b->velocity.x + b->velocity.y) > vlim )
    {
        b->velocity.x = (b->velocity.x / sqrt(b->velocity.x + b->velocity.y)) * vlim;
        b->velocity.y = (b->velocity.y / sqrt(b->velocity.x + b->velocity.y)) * vlim;
    }
}

void move_all_boids_to_new_positions() {

    sf::Vector2f v1, v2, v3;

    for (auto b : boidList)
    {
        v1 = rule1(b);
        v2 = rule2(b);
        v3 = rule3(b);

        b->velocity = b->velocity + v1 + v2 + v3;
        limit_velocity(b);
        b->position = b->position + b->velocity;
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");

    for (int i = 0; i < numberOfBoids; i++)
    {

        auto b = new Boid(sf::Vector2f(rand() % 1000,rand() % 1000));
        boidList.push_back(b);
    }

    while (window.isOpen())
    {
        window.clear();

        for (auto b : boidList)
        {
            b->Draw(window);
            move_all_boids_to_new_positions();
        }
        window.display();
    }

    return 0;
}