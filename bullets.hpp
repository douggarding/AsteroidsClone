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
#include "ship.hpp"

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
    
    
    void drawBullet(sf::RenderWindow &window);
    
    // Updates the position of a bullet for the current frame
    void updatePosition(int width, int height);
    
    // Destroys bullet if it's traveled its distance
    static void destroyBullets(std::vector<bullet>& bullets);

    // adds bullets to the vector of bullets
    static void makeBullets(std::vector<bullet>& bullets, const ship& playerShip, bool hasSpray);

};

#endif /* bullets_hpp */
