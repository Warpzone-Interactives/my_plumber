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
#include "player.hpp"
#include "constant.hpp"

void handle_window(sf::RenderWindow *window, std::vector<sf::Sprite> &sprites, player *player);
std::vector<std::vector<sf::Vector2f>> create_grid(int x_size);
void create_level(general_stat *g_stat);

//------------------------------------ init game ------------------------------------
std::vector<std::string> load_map(std::string filepath);
int init_error(general_stat g_stat);
general_stat init_general(char **av);
std::string get_where(std::string filepath);
void init_texture(general_stat *g_stat);

#endif
