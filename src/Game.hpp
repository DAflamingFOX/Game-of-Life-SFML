#pragma once

#include <SFML/Graphics.hpp>
#include "Grid.hpp"
#include "Camera.hpp"


class Game {
    public:
        Game();
        void run();

    private:
        void processEvents();
        void update();
        void render();

        sf::RenderWindow window;
        sf::View view;
        sf::Clock clock;
        sf::Font font;
        sf::Text uiText;

        Grid grid;
        Camera camera;
        bool running = true;
};