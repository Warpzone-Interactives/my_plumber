/*
** EPITECH PROJECT, 2025
** my_plumber
** File description:
** main
*/

#include "include/my.hpp"

sf::RenderWindow create_window(void)
{
    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "First window");
}

void analyse_events(sf::RenderWindow *window, sf::Event event)
{
    while ((*window).pollEvent(event)) {
        if (event.type == event.Closed)
            (*window).close();
    }
}

void handle_window(sf::RenderWindow *window)
{
    sf::Event event;

    analyse_events(window, event);
    return;
}
