/*
** EPITECH PROJECT, 2025
** my_plumber
** File description:
** init_general
*/

#include "game.hpp"

int game::getWhere(std::string filepath)
{
    std::ifstream input(filepath);
    std::string line;

    getline(input, line);
    _where = line;
    if (_where != "ow" && _where != "ug" && _where != "castle" && _where != "uw")
        return 1;
    return 0;
}

game::game(char *filepath, sf::RenderWindow *window, player *player)
{
    _player = player;
    _window = window;
    status = 0;
    scale = 1;
    if (getWhere(filepath) == 1)
        status += 1;
    _block = NULL;
    loadMap(filepath);
    initTexture();
}

void game::loadMap(std::string filepath)
{
    std::ifstream input(filepath);
    std::string line;

    getline(input, line);
    while (getline(input, line))
        _map.push_back(line);
    return;
}

void game::initTexture()
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

int game::getError()
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

int game::maxLength()
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

void game::createElement(char c, sf::Vector2f square)
{
    if (!_textures.count('/'))
        std::cout << "error\n";
    block *n_block = new block(square, c, getTexture(c), _block, scale);

    _block = n_block;
}


void game::createLine(const std::string &map_line, std::vector<sf::Vector2f> grid_line)
{
    for (size_t i = 0; i < map_line.size(); i++) {
        if (map_line[i] == ' ')
            continue;
        createElement(map_line[i], grid_line[i]);
    }
}

void game::createGrid(int x_size)
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

void game::createLevel()
{
    size_t count = 0;
    int lvlHeight = 0;
    for (const auto &line : _map) {
        lvlHeight += 1;
        for (char c : line)
            if (c != ' ')
                count++;
    }

    int level_length = maxLength();
    setScale(_window->getSize().y, lvlHeight);
    createGrid(level_length);
    for (size_t i = 0; i < _map.size(); i++)
        createLine(_map[i], grid[i]);
}

// -------------------| init map end |-------------------

// -------------------| game loop |-------------------

void game::key_event(sf::Event *event)
{
    switch (event->key.code) {
        case sf::Keyboard::Escape:
            _window->close();
            break;
        default:
            return;
    }
}

void game::analyse_events(sf::Event *event)
{
    switch (event->type) {
        case sf::Event::KeyPressed:
            key_event(event);
            break;
        case sf::Event::Closed:
            _window->close();
            break;
        default:
            return;
    }
}

void game::poll_event()
{
    sf::Event event;

    while (_window->pollEvent(event))
        analyse_events(&event);
}

void game::loop()
{
    sf::Clock frames;

    while (_window->isOpen())
        if (frames.getElapsedTime().asMilliseconds() > (1.0f)/60*1000) {
            poll_event();
            _window->clear();
            if (_block != NULL) {
                _block->anime();
                _block->draw(*_window);
            }
            _player->actualize(*_window);
            _window->display();
            frames.restart();
        }
}

// -------------------| game loop end |-------------------

void game::setScale(int ySize, int yNbElem)
{
    scale = ySize / yNbElem / 16;
}

sf::Texture game::getTexture(char c)
{
    if (c == 'a' || c == 's' || c == 'm' || c == 'f' || c == 'v')
        return _textures['?'];
    if (_textures.count(c)) {
        return  _textures[c];
    } else {
        return _textures['/'];
    }
}
