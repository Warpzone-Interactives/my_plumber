/*
** EPITECH PROJECT, 2025
** my_plumber
** File description:
** window related functions
*/

#include "include/my.hpp"

void analyse_events(sf::RenderWindow *window)
{
    sf::Event event;

    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window->close();
    }
}

void handle_window(sf::RenderWindow *window, std::vector<sf::Sprite>sprites)
{
    analyse_events(window);
    window->clear();
    for (const sf::Sprite &s : sprites)
        window->draw(s);
}
