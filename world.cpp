//
//  world.cpp
//  asteroids
//
//  Created by Westley Kirkham and Doug Garding on 9/18/17.
//
//

#include <stdlib.h> // to get random numbers
#include <cmath> // for the power and square root functions
#include <time.h> // uses this for the seed for the random number
#include <SFML/Graphics.hpp>
#include "world.hpp"
#include "ship.hpp"
#include "asteroid.hpp"



world::world(int w, int h){
    // Create seed for the random number generator
    srand (time(0));
    
    width = w;
    height = h;
    playerShip = ship::ship(20, width/2 - 10, height/2 - 10);
    
    // Create four level 3 asteroids for start of gae
    for (int i = 0; i < 4; i++){
        int direction = rand() % 359 + 1;
        sf::Vector2f startPos = asteroidStartPosition();
        asteroid rock = asteroid(3, startPos.x, startPos.y, direction, 0.3);
        asteroids.push_back(rock);
    }
}


/**
 * HELPER METHOD - ASTEROID STARTING POSITION
 * Gets two random points within the game window. These two points will be at least
 * 400 pixels away from the position of the ship. This is to prevent an unfair scenario
 * where asteroids spawn so close to the ship that there is no fair opportunity to avoid them.
 */
sf::Vector2f world::asteroidStartPosition(){
    
    // (x, y) values within world dimensions, but 400px away from ship:
    int xPos = 0;
    int yPos = 0;
    int distance = 0;
    do{
        xPos = rand() % width;
        yPos = rand() % height;
        
        // Distance formula to calculate distance between this coordinate and the ship coordinate
        distance = sqrt(pow((xPos - playerShip.getPos().x), 2) + pow((yPos - playerShip.getPos().y), 2));
        
    } while (distance <= 400);
    
    sf::Vector2f startPosition(xPos, yPos);
    return startPosition;
}


/**
 * RUNS THE GAME WINDOW AND GAME
 */
void world::runWorld(){
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(width, height), "Asteroids!", sf::Style::Close, settings);
    
    
    //
    // START GAME LOOP!!
    //
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
        
        // Clears the previous frame
        window.clear(sf::Color(44, 33, 68));
        
        
        // 1 - PROCESS USER INPUT
        
        playerShip.rotateRight();
        playerShip.rotateLeft();
        playerShip.thrusters(width, height);
        
        
        // 2 - UPDATE GAME STATE
        
        // Update object locations
        for(int i = 0; i < 4; i++){
            asteroids[i].updatePosition();
        }
        // playerShip.updatePosition();

        
        // 3 - RENDER THE GAME
        
        // Draw ship
        playerShip.drawShip(window);
        // Draw asteroids
        for(int i = 0; i < 4; i++){
            asteroids[i].drawAsteroid(window);
        }
        
        // Updates the display
        window.display();
    }
    //
    // END GAME LOOP
    //
    
}


/*
 Say you want your game to run at 60 FPS. That gives you about 16 milliseconds per frame. 
 As long as you can reliably do all of your game processing and rendering in less than 
 that time, you can run at a steady frame rate. All you do is process the frame and then 
 wait until it’s time for the next one
 */

