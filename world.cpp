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
#include <vector> // for bullet and asteroids vectors
#include "world.hpp"
#include "ship.hpp"
#include "asteroid.hpp"
#include "collisions.hpp"

world::world(int w, int h){
    // Create seed for the random number generator
    srand (time(0));
    
    width = w;
    height = h;
    playerShip = ship::ship(20, width/2 - 10, height/2 - 10);
    game_lvl = 1;
    
    // Create four level 3 asteroids for start of game
    asteroid::makeAsteroids(asteroids, game_lvl, height, width, playerShip.getPosition());
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
        window.clear(sf::Color(15, 12, 25));

        
        
        ///////////////////////
        // 1 - PROCESS USER INPUT
        ///////////////////////
        
        playerShip.rotateRight();
        playerShip.rotateLeft();
        playerShip.thrusters(width, height);
        
        
        sf::Time elapsed = clock.getElapsedTime();
        sf::Int32 msec = elapsed.asMilliseconds();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (msec > 100))
        {
            bullet::makeBullets(bullets, playerShip);
            clock.restart();
        }
        
        
        ///////////////////////
        // 2 - UPDATE GAME STATE
        ///////////////////////
        
        // Update level
        if (asteroids.size() == 0)
        {
            game_lvl++;
            drawLevel(window, game_lvl); // doesn't even make it to the screen. Need it to linger. display or clock?
            asteroid::makeAsteroids(asteroids, game_lvl, height, width, playerShip.getPosition());
        }
        
        // Detect bullet asteroid collisions
        for(int i = 0; i < asteroids.size(); i++){
            for(int j = 0; j < bullets.size(); j++){
                //Check if each bullet and astroid collide
                if(collisions::bulletAsteroid(bullets[j], asteroids[i])){
                    
                    // Spawn smaller asteroids if destroyed asteroid was large enough
                    asteroid tempAst = asteroids[i];
                    int asteroidLevel = tempAst.getLevel();
                    if(asteroidLevel > 1){
                        asteroid::makeAsteroids(asteroids, game_lvl, asteroidLevel-1, tempAst.getPosition());
                    }
                    
                    bullets.erase(bullets.begin() + j);
                    asteroids.erase(asteroids.begin() + i);
                    if(i > 0){
                        i--;
                    }
                    j--;
                }
            }
        }
        
        // Detect ship asteroid collisions
        for (int i = 0; i < asteroids.size(); i++){
            // Check if asteroid has collided with ship
            if(collisions::shipAsteroid(playerShip, asteroids[i])){
                playerShip.decrimentLives(width, height);
                playerShip.shipReset(clock, asteroids, playerShip, width, height);
            }
        }
        
        
        // Update astroid locations
        for(auto &element : asteroids){
            element.updatePosition(width, height);
        }
        
        // Update bullet locations
        for(auto &element : bullets){
            element.updatePosition(width, height);
        }
        
        // Destroy old bullets
        bullet::destroyBullets(bullets);
        
        
        ///////////////////////
        // 3 - RENDER THE GAME
        ///////////////////////
        
        // Draw ship
        playerShip.drawShip(window);
        
        // Draw asteroids
        for(auto element : asteroids){
            element.drawAsteroid(window);
        }
        
        // Draw bullets
        for(auto element : bullets){
            element.drawBullet(window);
        }

        // Draw lives
        playerShip.drawLives(window);
        
        // Updates the display
        window.display();
    }
    //
    // END GAME LOOP
    //
    
}



void world::drawLevel(sf::RenderWindow& window, int game_lvl)
{
    sf::Text text;
    sf::Font font;
    
    text.setFont(font);
    
    text.setString("Hello world");
    
    text.setCharacterSize(24);
    
    text.setFillColor(sf::Color::Red);
    
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    window.draw(text);
}

/*
 Say you want your game to run at 60 FPS. That gives you about 16 milliseconds per frame.
 As long as you can reliably do all of your game processing and rendering in less than 
 that time, you can run at a steady frame rate. All you do is process the frame and then 
 wait until it’s time for the next one
 */

