//
//  collisions.cpp
//  asteroids
//
//  Created by Westley Kirkham on 9/19/17.
//
//

#include "collisions.hpp"
#include <cmath> // for the power and square root functions



// Check if bullet collided with an asteroid
bool collisions::bulletAsteroid(bullet &b, asteroid &a){
    
    // get the position of the bullet and asteroid
    sf::Vector2f bPosition = b.getPosition();
    sf::Vector2f aPosition = a.getPosition();
    
    // Calculate distance between the two using distance formula
    int distance = sqrt(pow((bPosition.x - aPosition.x), 2) + pow((bPosition.y - aPosition.y), 2));
    
    return (distance <= (a.getRadius() + b.getSize().x));
}
