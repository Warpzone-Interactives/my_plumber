/*
** EPITECH PROJECT, 2025
** my_plumber
** File description:
** grid related functions
*/

#include "my.hpp"

std::vector<std::vector<sf::Vector2f>> create_grid(int x_size)
{
    std::vector<std::vector<sf::Vector2f>> grid;

    for (int j = 0; j < 15; j++) {
        std::vector<sf::Vector2f> line;
        for (int i = 0; i < x_size; i++) {
            sf::Vector2f square(i * 16, j * 16);
            line.push_back(square);
        }
        grid.push_back(line);
    }
    return grid;
}
