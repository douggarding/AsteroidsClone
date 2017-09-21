//
//  powerUp.cpp
//  asteroids
//
//  Created by Doug on 9/21/17.
//

#include "PowerUp.hpp"
#include "world.hpp"


// Constructor
PowerUp::PowerUp(std::string power){
    type = power;
    shape = buildShape(type);
}


sf::ConvexShape PowerUp::buildShape(std::string type){
    
    sf::ConvexShape shape;
    
    if (type == "shield"){
        shape.setPosition(PowerUpPosition());
        shape.setPointCount(3);
        shape.setPoint(0, sf::Vector2f(0, 0));
        shape.setPoint(1, sf::Vector2f(15, 50));
        shape.setPoint(2, sf::Vector2f(-15, 50));
        shape.setOrigin(0, 25);
        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineThickness(2);
        shape.setOutlineColor(sf::Color::Blue);
    }
    
    return shape;
}

// Adds a power up to an array of power ups
void PowerUp::addPowerUp(std::vector<PowerUp> &list){
    list.push_back(PowerUp("shield"));
}

// Draws a power up to the window
void PowerUp::drawPowerUp(sf::RenderWindow &window){
    window.draw(shape);
}

// Returns the bounds of the object for collisions
sf::FloatRect PowerUp::getBounds(){
    return shape.getGlobalBounds();
}

// Generates random starting point on map for the power up
sf::Vector2f PowerUp::PowerUpPosition(){
    
    int xPos = rand() % world::frameWidth;
    int yPos = rand() % world::frameHeight;
    
    sf::Vector2f startPosition(xPos, yPos);
    return startPosition;
}
