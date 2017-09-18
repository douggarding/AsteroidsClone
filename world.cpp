//
//  world.cpp
//  asteroids
//
//  Created by Westley Kirkham on 9/18/17.
//
//

#include "world.hpp"
#include <SFML/Graphics.hpp>


int main(int argc, const char * argv[]){
    
    sf::RenderWindow window(sf::VideoMode(1600, 1200), "Asteroids!", sf::Style::Close);
    
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
        
        window.clear(sf::Color::Blue);
        
        sf::CircleShape triangle( 80, 3);
        triangle.setFillColor(sf::Color::Black);
        triangle.setOutlineThickness(-3);
        triangle.setOutlineColor(sf::Color::White);
        triangle.setPosition(800, 600);
        
        window.draw(triangle);
        
        
        window.display();
    }
    
    
    
    
    return 0;
    
}
