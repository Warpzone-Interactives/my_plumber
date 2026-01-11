/*
** EPITECH PROJECT, 2025
** my_plumber
** File description:
** my.hpp
*/

#include "my.hpp"

#ifndef GENERAL
    #define GENERAL

class general_stat
{
public:
    int status;
    std::string where;
    std::vector<std::string> map;
    std::vector<sf::Sprite> sprites;
    // std::vector<sf::Texture> textures;
    std::map<char, sf::Texture> textures;
};

class block
{
public:
    sf::IntRect rect;
    sf::Sprite sprites;
    int nb_anim;
    block *next;
};

#endif