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
#include "PowerUp.hpp"
#include <string>
#include <iostream>

world::world(int w, int h){
    // Create seed for the random number generator
    srand (time(0));
    width = w;
    height = h;
    playerShip = ship::ship(20, width/2 - 10, height/2 - 10);
    game_lvl = 1;
    
    // Create four level 3 asteroids for start of game
    asteroid::makeAsteroids(asteroids, game_lvl, height, width, playerShip.getPosition());
    
    // start with a power up on screen
    PowerUp::addPowerUp(powerUps);
}


/**
 * RUNS THE GAME WINDOW AND GAME
 */
void world::runWorld(){
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(width, height), "---Asteroids---", sf::Style::Close, settings);
    
    sf::Font font;
    if (!font.loadFromFile("spaceAge.ttf"))
    {
        // error...
    }
    //
    // Title Screen
    //
    while (window.isOpen() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear(sf::Color(15, 12, 25));
        titleScreen(font, window);
        window.display();
    }
    
    
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
            drawLevel(window, font, clock, game_lvl);
            playerShip.addlife();
            playerShip.decrimentLives(width, height);
            asteroid::makeAsteroids(asteroids, game_lvl, height, width, playerShip.getPosition());
            bullets.erase(bullets.begin(), bullets.end());
        }
        
        // Insert power up
        
        // Detect ship power up collisions
        for(int i = 0; i < powerUps.size(); i++){
            if(collisions::shipPowerUp(playerShip, powerUps[i])){
                powerUps.erase(powerUps.begin() + i);
                i--;
            }
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
                bullets.erase(bullets.begin(), bullets.end());
                playerShip.shipReset(clock, asteroids, playerShip, width, height, window);
            }
        }
        if (playerShip.livesLeft() == 0)
        {
            gameOver(window, font, playerShip);
            game_lvl = 1;
            bullets.erase(bullets.begin(), bullets.end());
            asteroids.erase(asteroids.begin(), asteroids.end());
            asteroid::makeAsteroids(asteroids, game_lvl, height, width, playerShip.getPosition());
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

        // Draw Powerups
        for(auto element : powerUps){
            element.drawPowerUp(window);
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

void world::titleScreen(sf::Font& font, sf::RenderWindow& window)
{
    sf::Text text1;
    sf::Text text2;

    
    text1.setFont(font);
    text1.setString("Asteroids");
    text1.setPosition(width / 4, height / 3);
    text1.setCharacterSize(96);
    text1.setFillColor(sf::Color::White);
    text1.setStyle(sf::Text::Bold | sf::Text::Underlined);
    
    text2.setFont(font);
    text2.setString("Push Space to Start");
    text2.setPosition(width / 3.5, height / 2.4);
    text2.setCharacterSize(36);
    text2.setFillColor(sf::Color::White);
    
    window.draw(text1);
    window.draw(text2);


}

void world::drawLevel(sf::RenderWindow& window, sf::Font& font, sf::Clock& clock, int game_lvl)
{
    sf::Text text;
    
    std::string lvl = "Level " + std::to_string(game_lvl);
    text.setFont(font);
    text.setPosition(width / 3, height / 2.5);
    text.setString( lvl);
    text.setCharacterSize(96);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);

    clock.restart();
    sf::Time elapsed = clock.getElapsedTime();
    sf::Int32 msec = elapsed.asMilliseconds();
    do {
        elapsed = clock.getElapsedTime();
        msec = elapsed.asMilliseconds();
        window.clear(sf::Color(15, 12, 25));
        window.draw(text);
        window.display();
    } while (msec < 2000);

}

void world::gameOver(sf::RenderWindow& window, sf::Font& font, ship& playerShip)
{
    sf::Text text1;
    sf::Text text2;
    
    
    text1.setFont(font);
    text1.setString("Game Over");
    text1.setPosition(width / 4, height / 3);
    text1.setCharacterSize(108);
    text1.setFillColor(sf::Color::White);
    text1.setStyle(sf::Text::Bold);
    
    text2.setFont(font);
    text2.setString("Push Space to go again");
    text2.setPosition(width / 3.5, height / 2.4);
    text2.setCharacterSize(36);
    text2.setFillColor(sf::Color::White);
    
    window.draw(text1);
    window.draw(text2);
    do {
        window.clear(sf::Color(15, 12, 25));
        window.draw(text1);
        window.draw(text2);
        window.display();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return;
            }
        }
    } while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space));

    
    playerShip.decrimentLives(frameWidth, frameHeight);
    for(int i = 0; i < 4; i++)
    {
        playerShip.addlife();
    }
}

/*
 Say you want your game to run at 60 FPS. That gives you about 16 milliseconds per frame.
 As long as you can reliably do all of your game processing and rendering in less than 
 that time, you can run at a steady frame rate. All you do is process the frame and then 
 wait until it’s time for the next one
 */

