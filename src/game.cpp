#include "game.h"
#include "constants.h"
#include "SFML/Graphics.hpp"
#include <iostream>
Game::Game() {
    if(!this->font.loadFromFile("../resources/Pixeled.ttf")) {
        std::cout << "cannot load font" << std::endl;
    }
    this->applesVertexArray = sf::VertexArray(sf::Quads, 200);
    this->scoreText.setFont(this->font);
    this->scoreText.setPosition(sf::Vector2f(10.f, 10.f));
    this->scoreText.setCharacterSize(12);
    this->scoreText.setFillColor(sf::Color::White);

    this->gameOverText.setFont(this->font);
    this->gameOverText.setCharacterSize(24);
    this->gameOverText.setFillColor(sf::Color::White);
    this->gameOverText.setString("GAME OVER");
    this->gameOverText.setPosition(sf::Vector2f(SCREEN_WIDTH / 2 - this->gameOverText.getLocalBounds().width / 2, SCREEN_HEIGHT / 2  - this->gameOverText.getLocalBounds().height / 2));

    if(!this->appleEatSoundBuffer.loadFromFile("../resources/apple_eat.wav")) {
        std::cout << "could not load sound" << std::endl;
    }
    if(!this->gameOverSoundBuffer.loadFromFile("../resources/game_over.wav")) {
        std::cout << "could not load sound" << std::endl;
    }
    this->appleEatSound.setBuffer(this->appleEatSoundBuffer);
    this->gameOverSound.setBuffer(this->gameOverSoundBuffer);
    
    this->restart();
}
void Game::restart() {
    this->apples.clear();
    this->generateApple();
    this->snake.reinitialize();
    this->gameOver = false;
    this->score = 0;
}
void Game::generateApple() {
    this->apples.push_back(Apple {rand() % (SCREEN_WIDTH / CELL_SIZE), rand() % (SCREEN_HEIGHT / CELL_SIZE)});
}
void Game::updateVertexArray() {
    this->applesVertexArray.clear();
    this->applesVertexArray.resize(200);
    for(int i = 0; i < this->apples.size(); i++) {
        Apple apple = this->apples.at(i);
        this->applesVertexArray[i*4].position = sf::Vector2f(apple.x * CELL_SIZE, apple.y * CELL_SIZE);
        this->applesVertexArray[i*4+1].position = sf::Vector2f((apple.x+1) * CELL_SIZE, apple.y * CELL_SIZE);
        this->applesVertexArray[i*4+2].position = sf::Vector2f((apple.x+1) * CELL_SIZE, (apple.y+1) * CELL_SIZE);
        this->applesVertexArray[i*4+3].position = sf::Vector2f(apple.x * CELL_SIZE, (apple.y+1) * CELL_SIZE);
        this->applesVertexArray[i*4].color = sf::Color::Red;
        this->applesVertexArray[i*4+1].color = sf::Color::Red;
        this->applesVertexArray[i*4+2].color = sf::Color::Red;
        this->applesVertexArray[i*4+3].color = sf::Color::Red;
    }
}

void Game::setDirection(int x, int y) {
    this->snake.setDirection(x, y);
}

void Game::update() {
    if(!this->gameOver) {
        bool inBounds = (this->snake.getHead().x >= 0) && this->snake.getHead().x < (SCREEN_WIDTH / CELL_SIZE) && (this->snake.getHead().y >= 0) && (this->snake.getHead().y < SCREEN_HEIGHT / CELL_SIZE);
        if(this->snake.detectCollision() || !inBounds) {
            this->gameOver = true;
            this->gameOverClock.restart();
            this->gameOverSound.play();
        }
        else {
            this->snake.update();
            // handle apple eating
            for(int i = 0; i < this->apples.size(); i++) {
                Apple apple = this->apples.at(i);
                Cell snakeHead = this->snake.getHead();
                if(snakeHead.x == apple.x && snakeHead.y == apple.y) {
                    ++score;
                    this->snake.addLength(1);
                    this->apples.erase(this->apples.begin() + i);
                    this->generateApple();
                    this->appleEatSound.play();
                }
            }
            this->scoreText.setString(std::to_string(this->score) + " pts");
        }
    }
    else if(this->gameOverClock.getElapsedTime().asSeconds() > 2) {
        this->restart();
        this->gameOver = false;
    }
    
    this->updateVertexArray();
}