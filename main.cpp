/*
** EPITECH PROJECT, 2025
** my_plumber
** File description:
** main
*/

#include "my.hpp"

int lauch_game(char **av)
{
    std::vector<sf::Sprite> sprites;
    std::vector<sf::Texture> textures;
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "my_plumber");
    std::vector<std::string> map = load_map(av[1]);

    create_level(map, sprites, textures);
    while (window.isOpen())
        handle_window(&window, sprites);
    return 0;
}

// int loop(void)
// {
// }

int main(int ac, char **av)
{
    if (ac != 2)
        return 84;
    return lauch_game(av);
}
