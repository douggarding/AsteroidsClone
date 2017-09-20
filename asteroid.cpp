//
//  asteroid.cpp
//  asteroids
//
//  Created by Westley Kirkham on 9/19/17.
//
//

#include "asteroid.hpp"
#include "ship.hpp"
#include <cmath>
#include <stdlib.h>
#include <time.h> // uses this for the seed for the random number
#define PI 3.14159265


// Constructs an asteroid of size s (size can be 1, 2, or 3)
asteroid::asteroid(int lvl, int xPos, int yPos, int dir, float sp){
    level = lvl;
    direction = dir;
    speed = sp;
    
    if (level == 3)
        size = 60;
    else if (level == 2)
        size = 40;
    else
        size = 20;
    
    position.x = xPos;
    position.y = yPos;
    
    buildFrame();
}

// Creates the frame/shape of an astroid
void asteroid::buildFrame(){
    // Initialize the rock
    circle = sf::CircleShape();
    
    // Set the size of the rock
    circle.setRadius(size);
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineThickness(2);
    circle.setPosition(position.x, position.y);
    circle.setOrigin(size/2, size/2);
    
}

// Updates the asteroid's position
void asteroid::updatePosition(){
    
    // Keeps the asteroid within the bounds of the game/screen
    if (position.x >= 1600)
    {
        position.x = 0;
    }
    else if (position.x <= 0)
    {
        position.x = 1600 -1;
    }
    if (position.y >= 1200)
    {
        position.y = 0;
    }
    else if (position.y <= 0)
    {
        position.y = 1200 - 1;
    }
    
    position.x += -cos(direction * PI / 180 ) * speed;
    position.y += sin(direction * PI / 180 ) * speed;
    circle.setPosition(position.x, position.y);
}

// Draws an astroid to the window
void asteroid::drawAsteroid(sf::RenderWindow &window){
    window.draw(circle);
}




// When an astroid is destroid via collision
void asteroid::destroy(){

    
}




