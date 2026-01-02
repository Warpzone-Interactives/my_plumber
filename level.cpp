/*
** EPITECH PROJECT, 2025
** my_plumber
** File description:
** main
*/

#include "include/my.hpp"

int max_length(std::vector<std::string> map)
{
    int max = 0;
    int testing = 0;

    for (size_t i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++)
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

void create_element(char c, sf::Vector2f square,
    std::vector<sf::Sprite> &sprites, std::vector<sf::Texture> &textures)
{
    std::string filepath = "ressources/ow/" + choose_texture(c) + ".png";

    textures.emplace_back();
    textures.back().loadFromFile(filepath);

    sf::Sprite sprite(textures.back());
    sprite.setPosition(square);
    sprites.push_back(sprite);
}


void create_line(const std::string &map_line, std::vector<sf::Vector2f> grid_line,
    std::vector<sf::Sprite> &sprites, std::vector<sf::Texture> &textures)
{
    for (size_t i = 0; i < map_line.size(); i++) {
        if (map_line[i] == ' ')
            continue;
        create_element(map_line[i], grid_line[i], sprites, textures);
    }
}

void create_level(const std::vector<std::string> &map,
    std::vector<sf::Sprite> &sprites, std::vector<sf::Texture> &textures)
{
    size_t count = 0;
    for (const auto &line : map)
        for (char c : line)
            if (c != ' ')
                count++;
    sprites.reserve(count);
    textures.reserve(count);

    int level_length = max_length(map);
    std::vector<std::vector<sf::Vector2f>> grid = create_grid(level_length);

    for (size_t i = 0; i < map.size(); i++)
        create_line(map[i], grid[i], sprites, textures);
}