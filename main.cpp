/*
** EPITECH PROJECT, 2025
** my_plumber
** File description:
** main
*/

#include "include/my.hpp"

int main(int ac, char **av)
{
    std::vector<sf::Sprite> sprites;
    std::vector<sf::Texture> textures;

    if (ac < 2)
        return 84;
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "First window");
    auto map = load_map(av[1]);
    for (size_t i = 0; i < map.size(); i++)
        std::cout << map[i];
    create_level(map, sprites, textures);

    while (window.isOpen())
        handle_window(&window, sprites);
    return 0;
}
