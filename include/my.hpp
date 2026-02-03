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
#include <cmath>
#include <fstream>
#include <cstdio>
#include <iostream>
#include "block.hpp"
#include "player.hpp"
#include "game.hpp"
#include "constant.hpp"

void gameLoop(game *g_stat);
std::vector<std::string> load_map(std::string filepath);

#endif
