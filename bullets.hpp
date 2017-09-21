//
//  bullets.hpp
//  asteroids
//
//  Created by Westley Kirkham on 9/19/17.
//
//

#ifndef bullets_hpp
#define bullets_hpp
#include <SFML/Graphics.hpp>

class bullet{
    sf::RectangleShape rectangle;
    float distance;
    float speed;

    sf::RectangleShape buildBullet(sf::Vector2f pos, int rot);
    
public:
    bullet(sf::Vector2f pos, int rot);
    sf::RectangleShape getRectangle();
    bullet();
    void move(int width, int height);
    int getDistance();
    sf::Vector2f getPosition() const;
    int getRotation() const;
    sf::Vector2f getSize() const;


};

#endif /* bullets_hpp */
