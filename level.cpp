/*
** EPITECH PROJECT, 2025
** my_plumber
** File description:
** main
*/

#include "my.hpp"

int max_length(std::vector<std::string> map)
{
    int max = 0;
    int testing = 0;

    for (size_t i = 0; i < map.size(); i++) {
        for (size_t j = 0; j < map[i].size(); j++)
            testing++;
        if (testing > max)
            max = testing;
        testing = 0;
    }
    return max;
}

void create_element(char c, sf::Vector2f square, general_stat *g_stat)
{
    if (!g_stat->_textures.count('/'))
        std::cout << "error\n";
    block *n_block = new block(square, c, g_stat->get_texture(c), g_stat->_block);

    g_stat->_block = n_block;
}


void create_line(const std::string &map_line, std::vector<sf::Vector2f> grid_line, general_stat *g_stat)
{
    for (size_t i = 0; i < map_line.size(); i++) {
        if (map_line[i] == ' ')
            continue;
        create_element(map_line[i], grid_line[i], g_stat);
    }
}

void create_level(general_stat *g_stat)
{
    size_t count = 0;
    for (const auto &line : g_stat->_map)
        for (char c : line)
            if (c != ' ')
                count++;

    int level_length = max_length(g_stat->_map);
    std::vector<std::vector<sf::Vector2f>> grid = create_grid(level_length);

    for (size_t i = 0; i < g_stat->_map.size(); i++)
        create_line(g_stat->_map[i], grid[i], g_stat);
}