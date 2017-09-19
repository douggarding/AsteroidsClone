//
//  ship.hpp
//  asteroids
//
//  Created by Westley Kirkham and Doug Garding on 9/18/17.
//
//

#ifndef ship_hpp
#define ship_hpp
#include <SFML/Graphics.hpp>

class ship{
public:
    ship(int size, int xPos, int yPos);
    sf::CircleShape triangle;
    sf::Vector2f position;
    sf::Vector2f velocity; // contains initial velocity(Vo) and acceleration (a)
    int rotation;
    int lives;
    int size;
    
    sf::CircleShape buildFrame();
};


#endif /* ship_hpp */
