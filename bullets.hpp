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
    sf::Vector2f position;
    int rotation;
    int distance;
    float speed;

    sf::RectangleShape buildBullet();
    
public:
    bullet(sf::Vector2f pos, int rot);
    sf::RectangleShape getRectangle();
    bullet();
    void velocity(int width, int height);
    int getDistance();
};

#endif /* bullets_hpp */
