/*
** EPITECH PROJECT, 2025
** my_plumber
** File description:
** grid related functions
*/

#include "include/my.hpp"

sf::Vector2f **create_grid(int x_size)
{
    sf::Vector2f **grid;

    for (int i = 0; i < 15; i++) {
        sf::Vector2f *line;
        for (int j = 0; j < x_size; j++) {
            sf::Vector2f square;
            square.x = j * 16;
            square.y = i * 16;
            line[j] = square;
        }
        grid[i] = line;
    }
    return grid;
}
