//
//  bullets.hpp
//  asteroids
//
//  Created by Westley Kirkham on 9/19/17.
//
//

#ifndef bullets_hpp
#define bullets_hpp
#include "ship.hpp"
#include "SFML/Graphics.hpp"

class bullet{
    sf::RectangleShape rectangle;
    int distance;
    float speed;

    sf::RectangleShape buildBullet(sf::Vector2f pos, int rot);
    
public:
    bullet(sf::Vector2f pos, int rot);
    sf::RectangleShape getRectangle();
    bullet();
    void move(int width, int height);
    int getDistance();
    // Gets the asteroid's position
    sf::Vector2f getPosition();
};

#endif /* bullets_hpp */
