/*
** EPITECH PROJECT, 2025
** my_plumber
** File description:
** init_general
*/

#include "gstat.hpp"

general_stat::general_stat(char *map, sf::RenderWindow *window)
{
    _window = window;
    status = 0;
    scale = 1;
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
    _textures.insert({ 'X',  loading_texture});
    loading_texture.loadFromFile("ressources/" + where + "/coin.png");
    _textures.insert({ 'c',  loading_texture});
}

void general_stat::set_scale(int ySize, int yNbElem)
{
    scale = floor(ySize / yNbElem / 16);
}
sf::Texture general_stat::get_texture(char c)
{
    if (c == 'a' || c == 's' || c == 'm' || c == 'f' || c == 'v')
        return _textures['?'];
    if (_textures.count(c)) {
        return  _textures[c];
    } else {
        return _textures['/'];
    }
}
