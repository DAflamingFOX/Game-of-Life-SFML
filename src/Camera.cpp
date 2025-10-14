#include "Camera.hpp"

Camera::Camera() : view(sf::FloatRect({0, 0}, {800, 600})) {}

void Camera::handleEvent(const std::optional<sf::Event> &event, sf::RenderWindow &window)
{
    if (const auto *resize = event->getIf<sf::Event::Resized>())
    {
        float w = (float)resize->size.x;
        float h = (float)resize->size.y;
        auto center = view.getCenter();
        view.setSize({w * zoomLevel, h * zoomLevel});
        view.setCenter(center);
    }
    else if (const auto *scroll = event->getIf<sf::Event::MouseWheelScrolled>())
    {
        zoomLevel *= (scroll->delta > 0) ? 0.9f : 1.1f;
        view.zoom((scroll->delta > 0) ? 0.9f : 1.1f);
    }
    else if (const auto *mb = event->getIf<sf::Event::MouseButtonPressed>())
    {
        if (mb->button == sf::Mouse::Button::Right)
        {
            dragging = true;
            lastMouse = mb->position;
        }
    }
    else if (const auto *mr = event->getIf<sf::Event::MouseButtonReleased>())
    {
        if (mr->button == sf::Mouse::Button::Right)
        {
            dragging = false;
        }
    }
    else if (const auto *move = event->getIf<sf::Event::MouseMoved>())
    {
        if (dragging)
        {
            sf::Vector2i newMouse = move->position;
            sf::Vector2u winSize = window.getSize();
            sf::Vector2f worldPerPixel(view.getSize().x / winSize.x, view.getSize().y / winSize.y);
            sf::Vector2f delta = {(lastMouse.x - newMouse.x) * worldPerPixel.x, (lastMouse.y - newMouse.y) * worldPerPixel.y};
            view.move(delta);
            lastMouse = newMouse;
        }
    }
}

sf::View Camera::getView() const { return view; }