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

/// This describes the ship controlled by the player.
/// It includes a slightly more complex version of the
/// physics used by asteroids and bullets to move.
/// While thrusters are on (UP arrow is pressed) the
/// flame shows on the back of the ship. The player
/// begins the game with three lives. Upon collision
/// with an asteroid a life is lost and the ship is
/// placed back in the center of the screen.
class ship{
    sf::ConvexShape triangle;
    sf::ConvexShape flameShip;
    sf::ConvexShape shield;
    sf::Vector2f speed; // contains initial velocity(Vo) in x and y directions
    int old_rotation;
    int lives;
    bool drawShield;
    
    sf::ConvexShape buildFrame(int xPos, int yPos);
    sf::ConvexShape buildFlameFrame();
    sf::ConvexShape buildShield();
    
public:
    
    ship();
    ship(int size, int xPos, int yPos);
    void addlife();
    int livesLeft();
    void rotateRight();
    void rotateLeft();
    void thrusters(int width, int height);
    sf::CircleShape getShip();
    sf::Vector2f getPosition() const; /// We replaced certain sf::methods with our own. Get being the most common.
    int rotationGet() const;
    void setDrawShield(bool b);
    void drawShip(sf::RenderWindow &window);
    void drawLives(sf::RenderWindow& window);
    void decrimentLives(int width, int height);
    void incrementLives();
    static void shipReset(sf::Clock& clock, std::vector<asteroid>& asteroids, ship& playerShip, int width, int height, sf::RenderWindow& window);
    
    // Returns the bounds of the object for collisions
    sf::FloatRect getBounds(); /// For power-ups only.


    
};


#endif /* ship_hpp */
