//
//  ship.cpp
//  asteroids
//
//  Created by Westley Kirkham and Doug Garding on 9/18/17.
//
//

#include "ship.hpp"


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
