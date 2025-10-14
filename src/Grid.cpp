#include "Grid.hpp"

#include <cstdlib>
#include <ctime>

Grid::Grid(int cols, int rows, int cellSize) : cols(cols), rows(rows), cellSize(cellSize), worldWidth(cols * cellSize), worldHeight(rows * cellSize), history(500, std::vector<std::vector<bool>>(rows, std::vector<bool>(rows, false))), grid(rows, std::vector<bool>(cols, false)), nextGrid(rows, std::vector<bool>(cols, false))
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    randomize();
}

void Grid::randomize()
{
    for (int y = 0; y < rows; ++y)
        for (int x = 0; x < cols; ++x)
            grid[y][x] = (std::rand() % 5 == 0);
}

void Grid::clear()
{
    for (int y = 0; y < rows; ++y)
        for (int x = 0; x < cols; ++x)
            grid[y][x] = false;

    history.clear();
    iteration = 0;
}

void Grid::back()
{
    if (iteration == 0)
    {
        return;
    }
    if (!history.empty())
    {
        iteration--;
        grid = history.back();
        history.pop_back();
    }
}

void Grid::toggleCell(sf::Vector2f worldPosition)
{
    int cellX = static_cast<int>(worldPosition.x / cellSize);
    int cellY = static_cast<int>(worldPosition.y / cellSize);

    // Make sure we are inside bounds
    if (cellX >= 0 && cellX < cols && cellY >= 0 && cellY < rows)
    {
        grid[cellY][cellX] = !grid[cellY][cellX];

        // Clear history since previous states are now invalid.
        history.clear();
        iteration = 0;
    }
}

int Grid::getIteration()
{
    return iteration;
}

void Grid::step()
{
    iteration++;
    history.push_back(grid);
    if (history.size() > historyLimit)
        history.erase(history.begin());

    for (int y = 0; y < rows; ++y)
    {
        for (int x = 0; x < cols; ++x)
        {
            int neighbors = 0;
            for (int dy = -1; dy <= 1; ++dy)
            {
                for (int dx = -1; dx <= 1; ++dx)
                {
                    if (dx == 0 && dy == 0)
                        continue;
                    int nx = x + dx, ny = y + dy;
                    if (nx >= 0 && nx < cols && ny >= 0 && ny < rows)
                        if (grid[ny][nx])
                            ++neighbors;
                }
            }
            nextGrid[y][x] = grid[y][x]
                                 ? (neighbors == 2 || neighbors == 3)
                                 : (neighbors == 3);
        }
    }
    grid.swap(nextGrid);
}

void Grid::draw(sf::RenderWindow &window) const
{
    sf::RectangleShape cellShape({(float)cellSize, (float)cellSize});
    cellShape.setFillColor(sf::Color::White);

    sf::Color gridColor({50, 50, 50});

    // Draw cells
    for (int y = 0; y < rows; ++y)
    {
        for (int x = 0; x < cols; ++x)
        {
            if (grid[y][x])
            {
                cellShape.setPosition({x * cellSize, y * cellSize});
                window.draw(cellShape);
            }
        }
    }

    // Draw grid lines
    for (int x = 0; x <= cols; ++x)
    {
        float xpos = x * cellSize;
        sf::Vertex line[] = {
            {{xpos, 0.f}, gridColor},
            {{xpos, (float)worldHeight}, gridColor}};
        window.draw(line, 2, sf::PrimitiveType::Lines);
    }

    for (int y = 0; y <= rows; ++y)
    {
        float ypos = y * cellSize;
        sf::Vertex line[] = {
            {{0.f, ypos}, gridColor},
            {{(float)worldWidth, ypos}, gridColor}};
        window.draw(line, 2, sf::PrimitiveType::Lines);
    }
}