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


ship::ship(int s, int xPos, int yPos){
    size = s;
    position.x = xPos;
    position.y = yPos;
    velocity.x = 0;
    velocity.y = 0; // contains initial velocity(Vo) and acceleration (a)
    rotation = 0;
    lives = 3;
    triangle = buildFrame();
    
}

sf::CircleShape ship::buildFrame(){
    sf::CircleShape triangle(size, 3);
    triangle.setRadius(20);
    triangle.setFillColor(sf::Color::Black);
    triangle.setOutlineThickness(-3);
    triangle.setOutlineColor(sf::Color::White);
    triangle.setPosition(position.x, position.y);
    triangle.setOrigin(size/2, size/2);
    triangle.setRotation(rotation);
    return triangle;
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
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        position.y += -cos(rotation * PI / 180 );
        position.x += sin(rotation * PI / 180 );
    }
    triangle.setPosition(position.x, position.y);
}

sf::CircleShape ship::getShip()
{
    return triangle;
}




