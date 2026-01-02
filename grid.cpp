/*
** EPITECH PROJECT, 2025
** my_plumber
** File description:
** grid related functions
*/

#include "include/my.hpp"

std::vector<std::vector<sf::Vector2f>> create_grid(int x_size)
{
    std::vector<std::vector<sf::Vector2f>> grid;

    for (int i = 0; i < 15; i++) {
        std::vector<sf::Vector2f> line;
        for (int j = 0; j < x_size; j++) {
            sf::Vector2f square(j * 16, i * 16);
            line.push_back(square);
        }
        grid.push_back(line);
    }
    return grid;
}
