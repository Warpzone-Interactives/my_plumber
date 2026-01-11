/*
** EPITECH PROJECT, 2025
** my_plumber
** File description:
** get were the map is
*/

#include "my.hpp"

std::string get_where(std::string filepath)
{
    std::ifstream input(filepath);
    std::string line;
    std::string where;

    getline(input, line);
    where = line;
    if (where != "ow" && where != "ug" && where != "castel" && where != "uw")
        return "error";
    return where;
}
