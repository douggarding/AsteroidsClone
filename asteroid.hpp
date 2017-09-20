//
//  asteroid.hpp
//  asteroids
//
//  Created by Westley Kirkham on 9/19/17.
//
//

#ifndef asteroid_hpp
#define asteroid_hpp

#include <stdio.h>
#include "SFML/Graphics.hpp"

class asteroid{
private:
    int size;
    int level;
    float speed;
    sf::Vector2f position;
    sf::CircleShape circle;
    
    
    // Creates the frame/shape of an astroid
    void buildFrame(int xPos, int yPos, int dir);
    // Gets an initial starting position that is at least 50 away from the ship
    sf::Vector2f getStartPosition();
    
public:
    // asteroid Constructor
    asteroid(int size, int xPos, int yPos, int direction, float speed);
    // Draws an astroid to the window
    void drawAsteroid(sf::RenderWindow &window);
    // Updates the asteroid's position
    void updatePosition(int w, int h);
    // Gets the asteroid's position
    sf::Vector2f getPosition();
    // Gets the asteroid's size
    int getSize();
    // Gets the asteroid's rotation
    int getRotation();
};

#endif /* asteroid_hpp */
