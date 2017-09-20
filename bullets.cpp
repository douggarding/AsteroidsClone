//
//  bullets.cpp
//  asteroids
//
//  Created by Westley Kirkham on 9/19/17.
//
//
#include "bullets.hpp"


bullet::bullet(sf::Vector2f pos, int rot)
{
    position.x = pos.x;
    position.y = pos.y;
    rotation = rot;
    rectangle = buildBullet();
    distance = 0;

}

sf::RectangleShape bullet::buildBullet()
{
    sf::RectangleShape rectangle(sf::Vector2f(10, 5));
    rectangle.setFillColor(sf::Color::White);
    rectangle.setPosition(position.x, position.y);
    rectangle.setOrigin(-5, -7);
    rectangle.setRotation(rotation - 90);
    return rectangle;
}

sf::RectangleShape bullet::getRectangle()
{
    return rectangle;
}
