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

    while ((*window).pollEvent(event)) {
        if (event.type == event.Closed)
            (*window).close();
    }
}

void handle_window(sf::RenderWindow *window)
{
    analyse_events(window);
    return;
}
