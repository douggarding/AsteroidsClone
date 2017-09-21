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
#include "PowerUp.hpp"



class world{
private:
    // Width and height of window/game
    int width;
    int height;
    int game_lvl;
    ship playerShip;
    sf::Clock clock;
    std::vector<asteroid> asteroids;
    std::vector<bullet> bullets;
    std::vector<PowerUp> powerUps;
    
    bool bulletAsteroidCollision(bullet &b, asteroid &a);
    
public:
    // static ints that represent the width and height
    const static int frameWidth = 1600;
    const static int frameHeight = 1200;
    
    world(int w, int h);
    
    void runWorld();
    void drawBullets(std::vector<bullet>& bullets, sf::RenderWindow& window);
    void drawLevel(sf::RenderWindow& window, int game_lvl);

};

#endif /* world_hpp */
