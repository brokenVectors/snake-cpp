#ifndef SNAKE_H
#define SNAKE_H
#include "SFML/Graphics.hpp"
struct Cell {
    int x, y;
};
class Snake : public sf::Drawable {
    private:
    int xDirection = 1;
    int yDirection = 0;
    int length = 2;
    std::vector<Cell> body; // first cell = tail, last cell = head
    sf::VertexArray vertexArray;
    public:
    Snake();
    void reinitialize();
    void update();
    void updateVertexArray();
    Cell getHead();
    void setDirection(int x, int y);
    void addLength(int increment);
    bool detectCollision();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(this->vertexArray);
    }
};
#endif