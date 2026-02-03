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

// -------------------| init map |-------------------

int general_stat::max_length()
{
    int max = 0;
    int testing = 0;

    for (size_t i = 0; i < _map.size(); i++) {
        for (size_t j = 0; j < _map[i].size(); j++)
            testing++;
        if (testing > max)
            max = testing;
        testing = 0;
    }
    return max;
}

void general_stat::create_element(char c, sf::Vector2f square)
{
    if (!_textures.count('/'))
        std::cout << "error\n";
    block *n_block = new block(square, c, get_texture(c), _block, scale);

    _block = n_block;
}


void general_stat::create_line(const std::string &map_line, std::vector<sf::Vector2f> grid_line)
{
    for (size_t i = 0; i < map_line.size(); i++) {
        if (map_line[i] == ' ')
            continue;
        create_element(map_line[i], grid_line[i]);
    }
}

void general_stat::create_level()
{
    size_t count = 0;
    int level_with = 0;
    for (const auto &line : _map) {
        level_with += 1;
        for (char c : line)
            if (c != ' ')
                count++;
    }

    int level_length = max_length();
    set_scale(_window->getSize().y, level_with);
    std::vector<std::vector<sf::Vector2f>> grid = create_grid(level_length);
    for (size_t i = 0; i < _map.size(); i++)
        create_line(_map[i], grid[i]);
}

// -------------------| init map end |-------------------

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
