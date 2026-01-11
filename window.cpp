/*
** EPITECH PROJECT, 2025
** my_plumber
** File description:
** window related functions
*/

#include "my.hpp"

void key_event(sf::RenderWindow *window, sf::Event *event)
{
    switch (event->key.code) {
        case sf::Keyboard::Escape:
            window->close();
            break;
        default:
            return;
    }
}

void analyse_events(sf::Event *event, sf::RenderWindow *window)
{
    switch (event->type) {
        case sf::Event::KeyPressed:
            key_event(window, event);
            break;
        case sf::Event::Closed:
            window->close();
            break;
        default:
            return;
    }
}

void poll_event(sf::RenderWindow *window)
{
    sf::Event event;

    while (window->pollEvent(event))
        analyse_events(&event, window);
}

void handle_window(sf::RenderWindow *window, std::vector<sf::Sprite> &sprites)
{
    poll_event(window);
    window->clear();
    for (const sf::Sprite &s : sprites)
        window->draw(s);
    window->display();
}
