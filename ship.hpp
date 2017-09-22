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
#include "asteroid.hpp"

class ship{
    sf::ConvexShape triangle;
    sf::ConvexShape flameShip;
    sf::Vector2f speed; // contains initial velocity(Vo) in x and y directions
    int old_rotation;
    int lives;
    
    sf::ConvexShape buildFrame(int xPos, int yPos);
    sf::ConvexShape buildFlameFrame();
    
public:
    
    ship();
    ship(int size, int xPos, int yPos);
    void addlife();
    int livesLeft();
    void rotateRight();
    void rotateLeft();
    void thrusters(int width, int height);
    sf::CircleShape getShip();
    sf::Vector2f getPosition() const;
    int rotationGet() const;
    void drawShip(sf::RenderWindow &window);
    void drawLives(sf::RenderWindow& window);
    void decrimentLives(int width, int height);
    static void shipReset(sf::Clock& clock, std::vector<asteroid>& asteroids, ship& playerShip, int width, int height, sf::RenderWindow& window);
    
    // Returns the bounds of the object for collisions
    sf::FloatRect getBounds();


    
};


#endif /* ship_hpp */
