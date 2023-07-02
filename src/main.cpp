#include "SFML/Graphics.hpp"
#include "game.h"
#include "constants.h"
#include <iostream>
int main() {
    int directionX = 1;
    int directionY = 0;
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Snake!");
    sf::Clock clock;
    Game game;
    
    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Up) {
                    directionX = 0;
                    directionY = -1;
                }
                if(event.key.code == sf::Keyboard::Down) {
                    directionX = 0;
                    directionY = 1;
                }
                if(event.key.code == sf::Keyboard::Left) {
                    directionX = -1;
                    directionY = 0;
                }
                if(event.key.code == sf::Keyboard::Right) {
                    directionX = 1;
                    directionY = 0;
                }
            }
        }
        if(clock.getElapsedTime().asSeconds() >= 0.05) {
            game.setDirection(directionX, directionY);
            game.update();
            clock.restart();
        }
        window.clear(sf::Color::Black);
        window.draw(game);
        window.display();
        
    }
    return 0;
}