/*
** EPITECH PROJECT, 2025
** my_plumber
** File description:
** init_general
*/

#include "gstat.hpp"

int general_stat::getWhere(std::string filepath)
{
    std::ifstream input(filepath);
    std::string line;

    getline(input, line);
    _where = line;
    if (_where != "ow" && _where != "ug" && _where != "castle" && _where != "uw")
        return 1;
    return 0;
}

general_stat::general_stat(char *map, sf::RenderWindow *window)
{
    _window = window;
    status = 0;
    scale = 1;
    if (getWhere(map) == 1)
        status += 1;
    _block = NULL;
    _map = load_map(map);
    initTexture();
}

void general_stat::initTexture()
{
    sf::Texture loading_texture;

    loading_texture.loadFromFile("ressources/" + _where + "/placeholder.png");
    _textures.insert({ '/',  loading_texture});
    loading_texture.loadFromFile("ressources/" + _where + "/lucky_block.png");
    _textures.insert({ '?',  loading_texture});
    loading_texture.loadFromFile("ressources/" + _where + "/brick.png");
    _textures.insert({ 'b',  loading_texture});
    loading_texture.loadFromFile("ressources/" + _where + "/floor.png");
    _textures.insert({ 'x',  loading_texture});
    loading_texture.loadFromFile("ressources/" + _where + "/hard_block.png");
    _textures.insert({ 'X',  loading_texture});
    loading_texture.loadFromFile("ressources/" + _where + "/coin.png");
    _textures.insert({ 'c',  loading_texture});
}

int general_stat::getError()
{
    if (status == 0)
        return 0;
    if (status && 1 == 1)
        printf("error with the style of map\n");
    if (status && 2 == 2)
        printf("error with idk(exemple)\n");
    return 84;
}

// -------------------| init map |-------------------

int general_stat::maxLength()
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

void general_stat::createElement(char c, sf::Vector2f square)
{
    if (!_textures.count('/'))
        std::cout << "error\n";
    block *n_block = new block(square, c, getTexture(c), _block, scale);

    _block = n_block;
}


void general_stat::createLine(const std::string &map_line, std::vector<sf::Vector2f> grid_line)
{
    for (size_t i = 0; i < map_line.size(); i++) {
        if (map_line[i] == ' ')
            continue;
        createElement(map_line[i], grid_line[i]);
    }
}

void general_stat::createGrid(int x_size)
{
    for (int j = 0; j < 15; j++) {
        std::vector<sf::Vector2f> line;
        for (int i = 0; i < x_size; i++) {
            sf::Vector2f square(i * 16, j * 16);
            line.push_back(square);
        }
        grid.push_back(line);
    }
    return;
}

void general_stat::createLevel()
{
    size_t count = 0;
    int level_with = 0;
    for (const auto &line : _map) {
        level_with += 1;
        for (char c : line)
            if (c != ' ')
                count++;
    }

    int level_length = maxLength();
    setScale(_window->getSize().y, level_with);
    createGrid(level_length);
    for (size_t i = 0; i < _map.size(); i++)
        createLine(_map[i], grid[i]);
}

// -------------------| init map end |-------------------

void general_stat::setScale(int ySize, int yNbElem)
{
    scale = floor(ySize / yNbElem / 16);
}

sf::Texture general_stat::getTexture(char c)
{
    if (c == 'a' || c == 's' || c == 'm' || c == 'f' || c == 'v')
        return _textures['?'];
    if (_textures.count(c)) {
        return  _textures[c];
    } else {
        return _textures['/'];
    }
}
