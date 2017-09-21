//
//  ship.cpp
//  asteroids
//
//  Created by Westley Kirkham and Doug Garding on 9/18/17.
//
//

#include "ship.hpp"
#include "collisions.hpp"
#include <cmath>
#define PI 3.14159265

// Default constructor
ship::ship(){
    
}


ship::ship(int s, int xPos, int yPos){
    size = s;
    speed.x = 0.0;
    speed.y = 0.0;
    old_rotation = 0;
    lives = 3;
    triangle = buildFrame(xPos, yPos);
    flameShip = buildFlameFrame();
    
}

sf::ConvexShape ship::buildFrame(int xPos, int yPos){
    // Create the spaceship
    sf::ConvexShape spaceShip;
    spaceShip.setPosition(xPos, yPos);
    spaceShip.setPointCount(3);
    spaceShip.setPoint(0, sf::Vector2f(0, 0));
    spaceShip.setPoint(1, sf::Vector2f(15, 50));
    spaceShip.setPoint(2, sf::Vector2f(-15, 50));
    spaceShip.setOrigin(0, 25);
    spaceShip.setFillColor(sf::Color::Transparent);
    spaceShip.setOutlineThickness(3);
    spaceShip.setOutlineColor(sf::Color::White);
    
    return spaceShip;
}

// Creates a space ship with a flame
sf::ConvexShape ship::buildFlameFrame(){
    
    // Create the spaceship
    sf::ConvexShape spaceShip;
    spaceShip.setPointCount(7);
    spaceShip.setPoint(0, sf::Vector2f(0, 0));
    spaceShip.setPoint(1, sf::Vector2f(15, 50));
    spaceShip.setPoint(2, sf::Vector2f(10, 50));
    spaceShip.setPoint(3, sf::Vector2f(0, 65));
    spaceShip.setPoint(4, sf::Vector2f(-10, 50));
    spaceShip.setPoint(5, sf::Vector2f(10, 50));
    spaceShip.setPoint(6, sf::Vector2f(-15, 50));
    
    spaceShip.setOrigin(0, 25);
    spaceShip.setFillColor(sf::Color::Transparent);
    spaceShip.setOutlineThickness(3);
    spaceShip.setOutlineColor(sf::Color::White);
    
    return spaceShip;
}

// what I have makes the triangle move if you push up
// and rotates it if you push left or right. Try running
// it though. It is NOT intuitive. We're going to have to
// tinker with it.
void ship::rotateRight()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if (rotationGet() >= 360)
        {
            triangle.setRotation(0);
        }
        triangle.setRotation(rotationGet() + 1);
        flameShip.setRotation(rotationGet() + 1);
    }

}

void ship::rotateLeft()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if (rotationGet() <= 0)
        {
            triangle.setRotation(360);
        }
        triangle.setRotation(rotationGet() - 1);
        flameShip.setRotation(rotationGet() - 1);
    }

}

void ship::thrusters(int width, int height)
{
    if (getPosition().x >= width)
    {
        triangle.setPosition(0, getPosition().y);
    }
    else if (getPosition().x <= 0)
    {
        triangle.setPosition(width - 1, getPosition().y);
    }
    if (getPosition().y >= height)
    {
        triangle.setPosition(getPosition().x, 0);
    }
    else if (getPosition().y <= 0)
    {
        triangle.setPosition(getPosition().x, height - 1);
    }
    
    triangle.move( speed.x / 20, speed.y / 20);
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        float move_y = -cos(rotationGet() * PI / 180 ) / 20;
        float move_x = sin(rotationGet() * PI / 180 ) / 20;
        triangle.move(move_x, move_y);
        speed.y += -cos(rotationGet() * PI / 180 ) / 15;
        speed.x += sin(rotationGet() * PI / 180 ) / 15;
        if (speed.x > 20)
        {
            speed.x = 20;
        }
        else if(speed.x < -20)
        {
            speed.x = -20;
        }
        
        if (speed.y > 20)
        {
            speed.y = 20;
        }
        else if (speed.y < -20)
        {
            speed.y = -20;
        }
        
        old_rotation = rotationGet();
        
    }
    flameShip.setPosition(getPosition().x, getPosition().y);
}

void ship::drawShip(sf::RenderWindow& window){
    
    // If they up key is being pressed, flicker the flame
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        window.draw(flameShip);
    }
        
    // If the up key isn't being pressed, just draw the ship
    else{
        window.draw(triangle);
    }
}

sf::Vector2f ship::getPosition() const
{
    return triangle.getPosition();
}

int ship::rotationGet() const
{
    return triangle.getRotation();
}

int ship::getSize(){
    return size;
}

void ship::decrimentLives(int width, int height){
    speed.x = 0.0;
    speed.y = 0.0;
    old_rotation = 0;
    triangle.setPosition((width / 2) -10, (height / 2) - 10);
    lives--;
}

void ship::drawLives(sf::RenderWindow& window)
{
    sf::ConvexShape stationary_ship = triangle;
    int life_pos = 30;
    for (int life = 0; life < lives; life++)
    {
        stationary_ship.setRotation(0);
        stationary_ship.setScale(0.5, 0.5);
        stationary_ship.setPosition(life_pos * life + life_pos, life_pos);
        window.draw(stationary_ship);
    }
}

void ship::shipReset(sf::Clock clock, std::vector<asteroid> asteroids, ship playerShip, int width, int height)
{
    clock.restart();
    sf::Time elapsed = clock.getElapsedTime();
    sf::Int32 sec = elapsed.asSeconds();
    bool unsafe = false;
    do
    {
        bool unsafe = false;
        sf::Time elapsed = clock.getElapsedTime();
        sec = elapsed.asSeconds();
        for (auto &element : asteroids)
        {
            element.updatePosition(width, height);
            if(collisions::shipAsteroid(playerShip, element))
            {
                unsafe = true;
            }
        }
        
    }while(unsafe || sec < 0.1);
}
