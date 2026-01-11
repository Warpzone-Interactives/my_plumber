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

std::string choose_texture(char c)
{
    std::string texture;
    switch(c) {
        case 'b':
            texture = "brick";
            break;
        case '?':
            texture = "lucky_block";
            break;
        case 'x':
            texture = "floor";
            break;
        default:
            texture = "placeholder";
            break;
    }
    return texture;
}

void create_element(char c, sf::Vector2f square, general_stat *g_stat)
{
    sf::IntRect rect({0, 0}, {16, 16});
    sf::Sprite sprite;

    if ( g_stat->textures.count(c) ) {
        sprite.setTexture(g_stat->textures[c]);
    } else {
        sprite.setTexture(g_stat->textures['/']);
    }
    sprite.setTextureRect(rect);
    sprite.setPosition(square);
    g_stat->sprites.push_back(sprite);
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
    for (const auto &line : g_stat->map)
        for (char c : line)
            if (c != ' ')
                count++;
    g_stat->sprites.reserve(count);

    int level_length = max_length(g_stat->map);
    std::vector<std::vector<sf::Vector2f>> grid = create_grid(level_length);

    for (size_t i = 0; i < g_stat->map.size(); i++)
        create_line(g_stat->map[i], grid[i], g_stat);
}