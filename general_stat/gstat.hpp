/*
** EPITECH PROJECT, 2025
** my_plumber
** File description:
** my.hpp
*/

#include "my.hpp"

#ifndef GENERAL_HPP
    #define GENERAL_HPP

class general_stat
{
public:
    general_stat(char *map, sf::RenderWindow *window);
    ~general_stat() = default;

    int max_length();
    void create_element(char c, sf::Vector2f square);
    void create_line(const std::string &map_line, std::vector<sf::Vector2f> grid_line);
    void create_level();
    void set_scale(int ySize, int yNbElem);
    void init_texture();
    sf::Texture get_texture(char c);

    int scale;
    int status;
    std::string where;
    sf::RenderWindow *_window;
    std::vector<std::vector<sf::Vector2f>> grid;
    std::vector<std::string> _map;
    std::vector<sf::Sprite> _sprites;
    std::map<char, sf::Texture> _textures;
    block *_block; // next for chained list
};

#endif