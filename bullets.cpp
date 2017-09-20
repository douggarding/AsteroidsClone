//
//  bullets.cpp
//  asteroids
//
//  Created by Westley Kirkham on 9/19/17.
//
//
#include "bullets.hpp"
#include <cmath>
#define PI 3.14159265


bullet::bullet(sf::Vector2f pos, int rot)
{
    position.x = pos.x;
    position.y = pos.y;
    rotation = rot;
    rectangle = buildBullet();
    speed = 1.3;
    distance = 0;

}

sf::RectangleShape bullet::buildBullet()
{
    sf::RectangleShape rectangle(sf::Vector2f(10, 5));
    rectangle.setFillColor(sf::Color::White);
    rectangle.setPosition(position.x, position.y);
    rectangle.setOrigin(-30, 2);
    rectangle.setRotation(rotation - 90);
    return rectangle;
}

sf::RectangleShape bullet::getRectangle()
{
    return rectangle;
}


void bullet::velocity(int width, int height)
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
    
    position.y +=  -cos(rotation * PI / 180 ) * speed;
    position.x +=  sin(rotation * PI / 180 ) * speed;

    rectangle.setPosition(position.x, position.y);
    distance += (pow(cos(rotation * PI / 180 ), 2) + pow(sin(rotation * PI / 180 ), 2)) * speed;
    
}

int bullet::getDistance()
{
    return distance;
}

// Gets the asteroid's position
sf::Vector2f bullet::getPosition(){
    return position;
}
