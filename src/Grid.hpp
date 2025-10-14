#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Grid {
    public:
        Grid(int cols, int rows, int cellSize);
        void randomize();
        void clear();
        void step();
        void back();
        void toggleCell(sf::Vector2f worldPosition);
        int getIteration();
        void draw(sf::RenderWindow &window) const;

    private:
        int cols, rows, cellSize;
        int worldWidth, worldHeight;
        int historyLimit = 500;
        int iteration = 0;
        std::vector<std::vector<std::vector<bool>>> history;
        std::vector<std::vector<bool>> grid;
        std::vector<std::vector<bool>> nextGrid;
};