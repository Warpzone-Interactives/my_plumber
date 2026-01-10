/*
** EPITECH PROJECT, 2025
** my_plumber
** File description:
** map related functions
*/

#include "my.hpp"

std::vector<std::string> load_map(std::string filepath)
{
    std::ifstream input(filepath);
    std::vector<std::string> map;
    std::string line;

    getline(input, line);
    while (getline(input, line))
        map.push_back(line);
    return map;
}
