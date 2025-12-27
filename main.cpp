/*
** EPITECH PROJECT, 2025
** my_plumber
** File description:
** main
*/

#include "include/my.hpp"

int main(int ac, char **av)
{
    if (ac < 2)
        return 84;
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "First window");
    auto map = load_map(av[1]);
    for (size_t i = 0; i < map.size(); i++)
        std::cout << map[i];
    // display_map(map);

    while (window.isOpen())
        handle_window(&window);
    return 0;
}
