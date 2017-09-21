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
    makeAsteroids(asteroids, game_lvl);
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
        
        
        ///////////////////////
        // 1 - PROCESS USER INPUT
        ///////////////////////
        
        playerShip.rotateRight();
        playerShip.rotateLeft();
        playerShip.thrusters(width, height);
        
        
        ///////////////////////
        // 2 - UPDATE GAME STATE
        ///////////////////////
        
        // Update level
        if (asteroids.size() == 0)
        {
            game_lvl++;
            drawLevel(window, game_lvl); // doesn't even make it to the screen. Need it to linger. display or clock?
            makeAsteroids(asteroids, game_lvl);
        }
        
        // Detect bullet asteroid collisions
        for(int i = 0; i < asteroids.size(); i++){
            for(int j = 0; j < bullets.size(); j++){
                //Check if each bullet and astroid collide
                if(collisions::bulletAsteroid(bullets[j], asteroids[i])){
                    
                    bullets.erase(bullets.begin() + j);
                    asteroids.erase(asteroids.begin() + i);
                    i--;
                    j--;
                }
            }
        }
        
        // Update object locations
        for(auto &element : asteroids){
            element.updatePosition(width, height);
        }

        
        ///////////////////////
        // 3 - RENDER THE GAME
        ///////////////////////
        // Draw ship
        playerShip.drawShip(window);
        // Draw asteroids
        for(int i = 0; i < asteroids.size(); i++){
            asteroids[i].drawAsteroid(window);
        }
        
        // Draw bullets
        makeBullets(bullets, clock, playerShip); // ship method
        drawBullets(bullets, window); // world method

        // Draw lives
        playerShip.drawLives(window);
        
        // Updates the display
        window.display();
    }
    //
    // END GAME LOOP
    //
    
}


/**
 * HELPER METHOD - RANDOM ASTEROID STARTING POSITION
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
        distance = sqrt(pow((xPos - playerShip.positionGet().x), 2) + pow((yPos - playerShip.positionGet().y), 2));
        
    } while (distance <= 400);
    
    sf::Vector2f startPosition(xPos, yPos);
    return startPosition;
}

void world::makeAsteroids(std::vector<asteroid>& asteroids, int game_lvl)
{
    
    for (int i = 0; i < 3 + game_lvl; i++){
        int direction = rand() % 359 + 1;
        sf::Vector2f startPos = asteroidStartPosition();
        asteroid rock = asteroid(3, startPos.x, startPos.y, direction, 0.3);
        asteroids.push_back(rock);
    }
    
}
/**
 * I tried doing this as a part of the ship class or the bullet class,
 * but the implementation got too complicated so I left them here.
 */
void world::makeBullets(std::vector<bullet>& bullets, sf::Clock& clock, const ship& playerShip)
{
    sf::Time elapsed = clock.getElapsedTime();
    sf::Int32 msec = elapsed.asMilliseconds();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (msec > 100))
    {
        bullets.push_back(bullet(playerShip.positionGet(), playerShip.rotationGet()));
        clock.restart();
    }
}

void world::drawBullets(std::vector<bullet>& bullets, sf::RenderWindow& window)
{
    for (int i = 0; i < bullets.size(); i++)
    {
        bullets[i].move(width, height);
        window.draw(bullets[i].getRectangle());
        destroyBullets(bullets, i);
    }
}

void world::destroyBullets(std::vector<bullet>& bullets, int i)
{
    if (bullets[i].getDistance() > 600 )
    {
        bullets.erase (bullets.begin() + i);
        i--;
    }
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

