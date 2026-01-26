/*
** EPITECH PROJECT, 2025
** my_plumber
** File description:
** main
*/

#include "my.hpp"

int lauch_game(char **av)
{
    general_stat g_stat = init_general(av);
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "my_plumber");
    player player(0, {50.0f, 50.0f}, 'm');
    sf::Clock frames;

    if (g_stat.status != 0)
        return init_error(g_stat);
    create_level(&(g_stat));
    while (window.isOpen())
        if (frames.getElapsedTime().asMilliseconds() > (1.0f)/60*1000) {
            handle_window(&(window), g_stat.sprites, &player);
            frames.restart();
        }
    return 0;
}

// int loop(void)
// {
// }

int main(int ac, char **av)
{
    // std::map<char, std::string> my_map = {
    //     { 'b', "texture brick\n" },
    //     { 'B', "2\n" },
    //     { 'C', "3\n" }
    // };
    // my_map.insert({ '?', "lucky block\n" });
    // if ( my_map.count('?') ) {std::cout <<  "Yes";} else {std::cout << "Nop";}
    if (ac != 2)
        return 84;
    return lauch_game(av);
}
