//
//  ship.cpp
//  asteroids
//
//  Created by Westley Kirkham and Doug Garding on 9/18/17.
//
//

#include "ship.hpp"
#include <cmath>
#define PI 3.14159265

// Default constructor
ship::ship(){
    
}


ship::ship(int s, int xPos, int yPos){
    size = s;
    position.x = xPos;
    position.y = yPos;
    speed.x = 0.0;
    speed.y = 0.0;
    rotation = 0;
    old_rotation = 0;
    lives = 3;
    triangle = buildFrame();
    flameShip = buildFlameFrame();
    
}

sf::ConvexShape ship::buildFrame(){
    // Create the spaceship
    sf::ConvexShape spaceShip;
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
        if (rotation >= 360)
        {
            rotation = 0;
        }
    
        rotation += 1;
    }
    triangle.setRotation(rotation);
    flameShip.setRotation(rotation);
}

void ship::rotateLeft()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if (rotation <= 0)
        {
            rotation = 360;
        }
        
        rotation -= 1;
    }
    triangle.setRotation(rotation);
    flameShip.setRotation(rotation);
}

void ship::thrusters(int width, int height)
{
    if (position.x >= width)
    {
        position.x = 0;
    }
    else if (position.x <= 0)
    {
        position.x = width -1;
    }
    if (position.y >= height)
    {
        position.y = 0;
    }
    else if (position.y <= 0)
    {
        position.y = height - 1;
    }
    
    position.y +=  speed.y / 20;
    position.x +=  speed.x / 20;
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        position.y += -cos(rotation * PI / 180 ) / 20;
        position.x += sin(rotation * PI / 180 ) / 20;
        speed.y += -cos(rotation * PI / 180 ) / 15;
        speed.x += sin(rotation * PI / 180 ) / 15;
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
        
        old_rotation = rotation;
        
    }
    

    
    triangle.setPosition(position.x, position.y);
    flameShip.setPosition(position.x, position.y);
}

void ship::updatePosition(){
    position.x += 1;
    position.y += 1;
    triangle.setPosition(position.x, position.y);
    flameShip.setPosition(position.x, position.y);
}

void ship::drawShip(sf::RenderWindow &window){
    
    // If they up key is being pressed, flicker the flame
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        window.draw(flameShip);
    }
        
    // If the up key isn't being pressed, just draw the ship
    else{
        window.draw(triangle);
    }
}

sf::Vector2f ship::getPos()
{
    return position;
}

int ship::getRotation()
{
    return rotation;
}

