#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <iostream>
#include <format>
#include <string>

Game::Game() : window(sf::VideoMode({800, 600}), "Conway's Game of Life"), view(sf::FloatRect({0.f,0.f}, {800.f, 600.f})),
               grid(200, 200, 10), font(), uiText(font)
{
    window.setFramerateLimit(60);

    // Load font
    if (!font.openFromFile("fonts/MonaspaceNeonNF-Regular.otf"))
    {
        std::cerr << "Error loading font!" << std::endl;
    }

    // Create text object
    uiText.setFont(font);
    uiText.setCharacterSize(24);
    uiText.setFillColor(sf::Color::Green);
    uiText.setPosition({10, 10});
}

void Game::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }

        camera.handleEvent(event, window);

        if (const auto *resize = event->getIf<sf::Event::Resized>()) {
            float newWidth = static_cast<float>(resize->size.x);
            float newHeight = static_cast<float>(resize->size.y);

            sf::FloatRect visibleArea({0.f, 0.f}, {newWidth, newHeight});
            view = sf::View(visibleArea);
            window.setView(view);
        }
        else if (const auto *key = event->getIf<sf::Event::KeyPressed>())
        {
            switch (key->scancode)
            {
            case sf::Keyboard::Scancode::Space:
                running = !running;
                break;
            case sf::Keyboard::Scancode::R:
                grid.randomize();
                break;
            case sf::Keyboard::Scancode::C:
                grid.clear();
                break;
            case sf::Keyboard::Scancode::Right:
                if (!running)
                    grid.step();
                break;
            case sf::Keyboard::Scancode::Left:
                if (!running)
                    grid.back();
                break;
            default:
                break;
            }
        }
        else if (const auto *mb = event->getIf<sf::Event::MouseButtonPressed>())
        {
            if (!running && mb->button == sf::Mouse::Button::Left)
            {
                sf::Vector2f worldPos = window.mapPixelToCoords(mb->position, camera.getView());
                grid.toggleCell(worldPos);
            }
        }
    }
}

void Game::update()
{
    if (running && clock.getElapsedTime().asMilliseconds() > 100)
    {
        grid.step();
        clock.restart();
    }
}

void Game::render()
{
    window.clear(sf::Color::Black);

    window.setView(camera.getView());
    grid.draw(window);

    // UI
    window.setView(view);

    uiText.setString(running ? "Running" : "Paused");
    uiText.setPosition({10, 10});
    window.draw(uiText);

    uiText.setString(std::format("Iteration: {}", grid.getIteration()));
    uiText.setPosition({10, view.getSize().y - 24 - 10});
    window.draw(uiText);

    window.display();
}