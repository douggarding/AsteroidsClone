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

    rectangle = buildBullet(pos, rot);
    speed = 1.3;
    distance = 0;

}

sf::RectangleShape bullet::buildBullet(sf::Vector2f pos, int rot)
{
    sf::RectangleShape rectangle(sf::Vector2f(5, 15));
    rectangle.setFillColor(sf::Color::Green);
    rectangle.setPosition(pos.x, pos.y);
    rectangle.setOrigin(2, 25);
    rectangle.setRotation(rot);
    return rectangle;
}

sf::RectangleShape bullet::getRectangle()
{
    return rectangle;
}


void bullet::move(int width, int height)
{
    if (getPos().x >= width)
    {
        rectangle.setPosition(0, getPos().y);
    }
    else if (getPos().x <= 0)
    {
        rectangle.setPosition(width -1, getPos().y);
    }
    if (getPos().y >= height)
    {
        rectangle.setPosition(getPos().x, 0);

    }
    else if (getPos().y <= 0)
    {
        rectangle.setPosition(getPos().x, height - 1);
    }
    
    float y_update = getPos().y - cos(getRotation() * PI / 180 ) * speed;
    float x_update = getPos().x + sin(getRotation() * PI / 180 ) * speed;
    rectangle.setPosition(x_update, y_update);
    distance +=  speed;
    
}

int bullet::getDistance()
{
    return distance;
}

// Gets the asteroid's position
sf::Vector2f bullet::getPosition(){
    return position;
}
