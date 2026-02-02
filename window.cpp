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

void gameLoop(sf::RenderWindow *window, general_stat g_stat, player *player)
{
    sf::Clock frames;

    while (window->isOpen())
        if (frames.getElapsedTime().asMilliseconds() > (1.0f)/60*1000) {
            poll_event(window);
            window->clear();
            if (g_stat._block != NULL) {
                g_stat._block->anime();
                g_stat._block->draw(*window);
            }
            // for (const sf::Sprite &s : sprites)
            //     window->draw(s);
            player->actualize(*window);
            window->display();
            frames.restart();
        }
}
