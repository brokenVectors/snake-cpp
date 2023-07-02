#include "snake.h"
#include "constants.h"
#include <iostream>
Snake::Snake() {
    // setup the vertex array
    this->vertexArray = sf::VertexArray(sf::Quads, 200);
    this->reinitialize();
}
void Snake::reinitialize() {
    this->length = 2;
    this->body = std::vector<Cell> {
        Cell {10, 10},
        Cell {11, 10}
    };
}
void Snake::update() {
    Cell lastHead = this->getHead();
    body.push_back(
        Cell {
                lastHead.x + this->xDirection,
                lastHead.y + this->yDirection
            }
    );
    if(body.size() > this->length) {
        // get rid of tail
        body.erase(body.begin());
    }
    this->updateVertexArray();
}
Cell Snake::getHead() {
    return this->body.back();
}
void Snake::addLength(int increment) {
    this->length += increment;
}
bool Snake::detectCollision() {
    Cell head = this->getHead();
    for(int i = 0; i < this->body.size(); i++) {
        Cell cell = this->body.at(i);
        bool isHead = i == this->body.size()-1;
        if(
            cell.x == head.x
            && cell.y == head.y
            && !isHead
        ) {
            return true;
        }
    }
    return false;
}
void Snake::updateVertexArray() {
    this->vertexArray.clear();
    this->vertexArray.resize(200);
    for(int i = 0; i < this->body.size(); i++) {
        Cell cell = this->body.at(i);
        this->vertexArray[i*4].position = sf::Vector2f(cell.x * CELL_SIZE, cell.y * CELL_SIZE);
        this->vertexArray[i*4+1].position = sf::Vector2f((cell.x+1) * CELL_SIZE, cell.y * CELL_SIZE);
        this->vertexArray[i*4+2].position = sf::Vector2f((cell.x+1) * CELL_SIZE, (cell.y+1) * CELL_SIZE);
        this->vertexArray[i*4+3].position = sf::Vector2f(cell.x * CELL_SIZE, (cell.y+1) * CELL_SIZE);

        this->vertexArray[i*4].color = sf::Color::Green;
        this->vertexArray[i*4+1].color = sf::Color::Green;
        this->vertexArray[i*4+2].color = sf::Color::Green;
        this->vertexArray[i*4+3].color = sf::Color::Green;
    }
}

void Snake::setDirection(int x, int y) {
    if(this->xDirection != -x && this->yDirection != -y) {
        this->xDirection = x;
        this->yDirection = y;
    }   
}
