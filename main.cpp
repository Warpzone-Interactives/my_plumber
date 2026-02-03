/*
** EPITECH PROJECT, 2025
** my_plumber
** File description:
** main
*/

#include "my.hpp"

int lauch_game(char **av)
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "my_plumber", sf::Style::Fullscreen);
    player player(0, {50.0f, 50.0f}, 'm');
    game g_stat(av[1], &window, &player);

    if (g_stat.getError() != 0)
        return 84;
    g_stat.createLevel();
    gameLoop(&g_stat);
    return 0;
}

#include <list>
int main(int ac, char **av)
{
    if (ac != 2)
        return 84;
    return lauch_game(av);
}
