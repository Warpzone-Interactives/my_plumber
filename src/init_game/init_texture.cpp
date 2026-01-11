/*
** EPITECH PROJECT, 2025
** my_plumber
** File description:
** init_texture
*/

#include "my.hpp"

void init_texture(general_stat *g_stat)
{

    sf::Texture texture;

    texture.loadFromFile("ressources/" + g_stat->where + "/placeholder.png");
    g_stat->textures.insert({ '/',  texture});
    texture.loadFromFile("ressources/" + g_stat->where + "/lucky_block.png");
    g_stat->textures.insert({ '?',  texture});
    texture.loadFromFile("ressources/" + g_stat->where + "/brick.png");
    g_stat->textures.insert({ 'b',  texture});
    texture.loadFromFile("ressources/" + g_stat->where + "/floor.png");
    g_stat->textures.insert({ 'x',  texture});
    texture.loadFromFile("ressources/" + g_stat->where + "/hard_block.png");
    g_stat->textures.insert({ 'h',  texture});
    texture.loadFromFile("ressources/" + g_stat->where + "/coin.png");
    g_stat->textures.insert({ 'c',  texture});
}