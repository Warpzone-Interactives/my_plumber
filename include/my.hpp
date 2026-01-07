/*
** EPITECH PROJECT, 2025
** my_plumber
** File description:
** my.hpp
*/

#ifndef MY_HPP
    #define MY_HPP
    #include <SFML/Graphics.hpp>
    #include <SFML/Window.hpp>
    #include <SFML/System.hpp>
    #include <SFML/Audio.hpp>
    #include <fstream>
    #include <cstdio>
    #include <iostream>
    #include "struct.hpp"

void handle_window(sf::RenderWindow *window, std::vector<sf::Sprite> &sprites);
std::vector<std::vector<sf::Vector2f>> create_grid(int x_size);
std::vector<std::string> load_map(std::string filepath);
void create_level(const std::vector<std::string> &map,
    std::vector<sf::Sprite> &sprites, std::vector<sf::Texture> &textures);

#endif
