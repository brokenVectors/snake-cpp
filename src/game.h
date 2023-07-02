#ifndef GAME_H
#define GAME_H
#include "snake.h"
#include <vector>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
struct Apple {
    int x, y;
};
class Game : public sf::Drawable {
    private:
    Snake snake;
    std::vector<Apple> apples;
    sf::Clock gameOverClock;
    sf::Font font;
    sf::Text scoreText;
    sf::Text gameOverText;
    sf::SoundBuffer appleEatSoundBuffer;
    sf::SoundBuffer gameOverSoundBuffer;
    sf::Sound appleEatSound;
    sf::Sound gameOverSound;
    sf::VertexArray applesVertexArray;
    int score = 0;
    bool gameOver = false;
    public:
    Game();
    void generateApple();
    void updateVertexArray();
    void restart();
    void setDirection(int x, int y); // interfaces with the Snake
    void update();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(this->snake);
        target.draw(this->applesVertexArray);
        target.draw(this->scoreText);
        if(this->gameOver) {
            target.draw(this->gameOverText);
        }
        
    }
};
#endif