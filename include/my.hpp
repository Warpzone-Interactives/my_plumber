/*
** EPITECH PROJECT, 2025
** my_plumber
** File description:
** my.hpp
*/

#ifndef MY_HPP_
    #define MY_HPP_
    #include <SFML/Graphics.hpp>
    #include <SFML/Window.hpp>
    #include <SFML/System.hpp>
    #include <SFML/Audio.hpp>
    #include <fstream>
    #include <cstdio>
    #include <iostream>

void handle_window(sf::RenderWindow *window, std::vector<sf::Sprite> sprites);
sf::Vector2f **create_grid(int x_size);
std::vector<std::string> load_map(std::string filepath);
void create_level(const std::vector<std::string> &map,
    std::vector<sf::Sprite> &sprites, std::vector<sf::Texture> &textures);

#endif
