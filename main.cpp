
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
    ship player_ship = ship(20, width/2 - 10, height/2 - 10);
    
    
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
        
                window.draw(player_ship.getShip());
        
        player_ship.rotateRight();
        player_ship.rotateLeft();
        player_ship.thrusters(width, height);

        
        window.display();
    }
    
    
    
    
    return 0;
    
}
