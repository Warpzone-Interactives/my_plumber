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

    int getError();
    void createLevel();
    sf::Texture getTexture(char c);

    int status;
    block *_block; // next for chained list

private:

    void loadMap(std::string filepath);
    int getWhere(std::string filepath);
    void setScale(int ySize, int yNbElem);
    void initTexture();
    int maxLength();
    void createElement(char c, sf::Vector2f square);
    void createLine(const std::string &map_line, std::vector<sf::Vector2f> grid_line);
    void createGrid(int x_size);

    int scale;
    std::string _where;
    sf::RenderWindow *_window;
    std::vector<std::vector<sf::Vector2f>> grid;
    std::vector<std::string> _map;
    std::vector<sf::Sprite> _sprites;
    std::map<char, sf::Texture> _textures;
};

#endif