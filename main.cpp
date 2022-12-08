/*Boids in SFML and C++, for Cpp Beyond the Basics.
Visualization: https://youtu.be/FQ1Xen5iCxQ
Written by Zubaydah Koelemeij
08/12/2022*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Boid.h"

using namespace std;

vector<Boid*> boidList;
int numberOfBoids = 30;

//Rule1: Boids try to fly towards the centre of mass of neighbouring boids.
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

    pcJ = sf::Vector2f(pcJ.x / 50, pcJ.y / 50); // tweak 100

    return pcJ;

}

//Rule2: Boids try to keep a small distance away from other objects(including other boids).
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

//Rule 3: Boids try to match velocity with near boids.
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
        pvJ = sf::Vector2f(pvJ.x / 1, pvJ.y / 1); // tweak 8
        return pvJ;

}

void limitVelocity(Boid *b)
{
    int vlim = 4; // Tweak velocity speed
    sf::Vector2f v;

    if( sqrt(b->velocity.x + b->velocity.y) > vlim )
    {
        b->velocity.x = (b->velocity.x / sqrt(b->velocity.x + b->velocity.y)) * vlim * 0.01;
        b->velocity.y = (b->velocity.y / sqrt(b->velocity.x + b->velocity.y)) * vlim * 0.01;
    }
}

void newPositionForBoids() 
{

    sf::Vector2f v1, v2, v3;

    for (auto b : boidList)
    {
        v1 = rule1(b);
        v2 = rule2(b);
        v3 = rule3(b);

        b->velocity = b->velocity + v1 + v2 + v3;
        limitVelocity(b);
        b->position = b->position + b->velocity;
    }
}

//Bounding the position
sf::Vector2f boundPosition(Boid b)
{
    int Xmin = 500;
    int Xmax = 500; 
    int Ymin = 500; 
    int Ymax = 500;

    sf::Vector2f v;

    for (auto b : boidList)
    {
        if (b->position.x < Xmin)
        {
            v.x = 10;
        }
        else if (b->position.x > Xmax)
        {
            v.x = -10;
        }

        if (b->position.y < Ymin)
        {
            v.y = 10;
        }
        else if (b->position.y > Ymax)

        {
            v.y = -10;
        }
        return v;
    }
 }

int main()
{
    const unsigned WINDOW_WIDTH = 1000;
    const unsigned WINDOW_HEIGHT = 1000;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");
    window.setFramerateLimit(120);


    for (int i = 0; i < numberOfBoids; i++)
    {

        auto b = new Boid(sf::Vector2f(rand() % 1000,rand() % 1000)); //procedure puts all the boids at a starting position
        boidList.push_back(b);
    }

    //drawing the window
    while (window.isOpen()) 
    {

        window.clear();

        for (auto b : boidList)
        {
            b->Draw(window);
            boundPosition;
            newPositionForBoids();
        }
        window.display();
    }

    return 0;
}