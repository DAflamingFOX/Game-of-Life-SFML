#pragma once
#include <SFML/Graphics.hpp>
#include <optional>

class Camera {
    public:
        Camera();
        void handleEvent(const std::optional<sf::Event> &event, sf::RenderWindow &window);
        sf::View getView() const;

        private:
            sf::View view;
            float zoomLevel = 1.f;
            bool dragging = false;
            sf::Vector2i lastMouse;
};