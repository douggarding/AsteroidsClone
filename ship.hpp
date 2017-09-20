//
//  ship.hpp
//  asteroids
//
//  Created by Westley Kirkham and Doug Garding on 9/18/17.
//
//

#ifndef ship_hpp
#define ship_hpp
#include "SFML/Graphics.hpp"

class ship{
    sf::CircleShape triangle;
    sf::Vector2f position;
    sf::Vector2f velocity; // contains initial velocity(Vo) and acceleration (a)
    int rotation;
    int lives;
    int size;
    
    sf::CircleShape buildFrame();
    
public:
    ship();
    ship(int size, int xPos, int yPos);
    void rotateRight();
    void rotateLeft();
    void thrusters(int width, int height);
    sf::CircleShape getShip();
    sf::Vector2f getPos();
    int getRotation();
    void updatePosition();
    void drawShip(sf::RenderWindow &window);
    
    
};


#endif /* ship_hpp */
