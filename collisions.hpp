//
//  collisions.hpp
//  asteroids
//
//  Created by Westley Kirkham on 9/19/17.
//
//

#ifndef collisions_hpp
#define collisions_hpp

#include <stdio.h>
#include "bullets.hpp"
#include "asteroid.hpp"
#include "ship.hpp"

class collisions{
public:
    // Detects a collision between an Asteroid and a Bullet
    static bool bulletAsteroid(bullet &b, asteroid &a);
};


#endif /* collisions_hpp */

