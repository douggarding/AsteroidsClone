//
//  world.hpp
//  asteroids
//
//  Created by Westley Kirkham and Doug Garding on 9/18/17.
//
//

#ifndef world_hpp
#define world_hpp

#include "SFML/Graphics.hpp"
#include <stdio.h>
#include "ship.hpp"
#include "asteroid.hpp"
#include "bullets.hpp"
#include "collisions.hpp"



class world{
private:
    // Width and height of window/game
    int width;
    int height;
    ship playerShip;
    std::vector<asteroid> asteroids;
public:
    world(int w, int h);
    
    // Creates a starting position that is 30 pixels away from the ship
    sf::Vector2f asteroidStartPosition();
    void runWorld();
    
};

#endif /* world_hpp */
