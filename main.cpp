/*
** EPITECH PROJECT, 2025
** my_plumber
** File description:
** main
*/

#include "my.hpp"

int lauch_game(char **av)
{
    player player1(0, {32.0f, 800.0f}, 'm');
    player player2(0, {100.0f, 800.0f}, 'l');
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "my_plumber");
    sf::View view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
    game game(av[1], &window, &view, &player1, NULL);

    if (game.getError() != 0)
        return 84;
    game.initLevel();
    game.loop();
    return 0;
}

int main(int ac, char **av)
{
    if (ac != 2)
        return 84;
    return lauch_game(av);
}
