
//
//  main.cpp
//  asteroids
//
//  Created by Westley Kirkham and Doug Garding on 9/18/17.
//
//
#include "world.hpp"
#include <SFML/Graphics.hpp>
#include "ship.hpp"
#include <cmath>

int main(int argc, const char * argv[]){
    
    int width = 1600;
    int height = 1200;
    
    sf::RenderWindow window(sf::VideoMode(width, height), "Asteroids!", sf::Style::Close);
    
    // We'll have to move these into the while loop later. They can be
    // reset if the game ends and they want to try again or if they move
    // on to the next level. We may not want to show the ship initially,
    // but wait a few seconds. It depends, it's mostly a stylistic option.
    // Most of this can/should also be moved to methods/constructors.
    ship player_ship;
    player_ship.size = 20;
    player_ship.position.x = (width/2 - player_ship.size);
    player_ship.position.y = (height/2 - player_ship.size);
    player_ship.rotation = 0;
    player_ship.lives = 3;
    
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        
        window.clear(sf::Color(44, 33, 68));
        
        sf::CircleShape triangle(player_ship.size, 3);
        triangle.setFillColor(sf::Color::Black);
        triangle.setOutlineThickness(-3);
        triangle.setOutlineColor(sf::Color::White);
        triangle.setPosition(player_ship.position.x, player_ship.position.y);
        triangle.setOrigin(player_ship.size/2, player_ship.size/2);
        triangle.setRotation(player_ship.rotation);
        window.draw(triangle);
        
        
        // what I have makes the triangle move if you push up
        // and rotates it if you push left or right. Try running
        // it though. It is NOT intuitive. We're going to have to
        // tinker with it.
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            if (player_ship.rotation <= 0)
            {
                player_ship.rotation = 360;
            }
            
            player_ship.rotation -= 1;
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            if (player_ship.rotation >= 360)
            {
                player_ship.rotation = 0;
            }
            
            player_ship.rotation += 1;

        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            player_ship.position.y += cos(player_ship.rotation);
            player_ship.position.x += sin(player_ship.rotation);
        }
        
        window.display();
    }
    
    
    
    
    return 0;
    
}
