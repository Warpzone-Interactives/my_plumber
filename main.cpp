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
    general_stat g_stat(av[1], &window);
    player player(0, {50.0f, 50.0f}, 'm');

    if (!g_stat._textures.count('/'))
        std::cout << "error\n";
    if (g_stat.status != 0)
        return init_error(g_stat);
    create_level(&(g_stat));
    gameLoop(&(window), g_stat, &player);
    return 0;
}

#include <list>
int main(int ac, char **av)
{
    if (ac != 2)
        return 84;
    return lauch_game(av);
}
