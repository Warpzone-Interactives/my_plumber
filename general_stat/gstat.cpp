/*
** EPITECH PROJECT, 2025
** my_plumber
** File description:
** init_general
*/

#include "gstat.hpp"

general_stat::general_stat(char *map)
{
    status = 0;
    where = get_where(map);
    if (where == "error")
        status += 1;
    _block = NULL;
    _map = load_map(map);
    init_texture();
    if (!_textures.count('/'))
        std::cout << "error\n";
}

void general_stat::init_texture()
{
    sf::Texture loading_texture;

    loading_texture.loadFromFile("ressources/" + where + "/placeholder.png");
    _textures.insert({ '/',  loading_texture});
    loading_texture.loadFromFile("ressources/" + where + "/lucky_block.png");
    _textures.insert({ '?',  loading_texture});
    loading_texture.loadFromFile("ressources/" + where + "/brick.png");
    _textures.insert({ 'b',  loading_texture});
    loading_texture.loadFromFile("ressources/" + where + "/floor.png");
    _textures.insert({ 'x',  loading_texture});
    loading_texture.loadFromFile("ressources/" + where + "/hard_block.png");
    _textures.insert({ 'h',  loading_texture});
    loading_texture.loadFromFile("ressources/" + where + "/coin.png");
    _textures.insert({ 'c',  loading_texture});
}

sf::Texture general_stat::get_texture(char c)
{
    if (_textures.count(c)) {
        return  _textures[c];
    } else {
        return _textures['/'];
    }
}
