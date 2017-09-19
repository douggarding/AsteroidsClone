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

struct ship{
    sf::Vector2f position;
    sf::Vector2f velocity; // contains initial velocity(Vo) and acceleration (a)
    int rotation;
    int lives;
    int size;
};


#endif /* ship_hpp */
