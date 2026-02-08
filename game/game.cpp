/*
** EPITECH PROJECT, 2025
** my_plumber
** File description:
** init_general
*/

#include "game.hpp"

// -------------------| init game |-------------------

game::game(char *filepath, sf::RenderWindow *window, player *player)
{
    _player = player;
    _window = window;
    _window->setFramerateLimit(60);
    animClock = new gameClock({1, 0.25, 0.25, 0.25});
    status = 0;
    scale = 1;
    if (getWhere(filepath) == 1)
        status += 1;
    _block = NULL;
    loadMap(filepath);
    get_Size();
    initLstBlock();
    initBlockTexture();
}

void game::initLstBlock()
{
    std::vector<block *> lst;
    for (int y = 0; y < width; y++) {
        lst.push_back(NULL);
    }
    for (int x = 0; x < length; x++) {
        lstBlock.push_back(lst);
        
    }
}

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

void game::loadMap(std::string filepath)
{
    std::ifstream input(filepath);
    std::string line;

    getline(input, line);
    while (getline(input, line))
        _map.push_back(line);
    return;
}

void game::initBlockTexture()
{
    sf::Texture loading_texture;

    loading_texture.loadFromFile("ressources/" + _where + "/placeholder.png");
    _blockTextures.insert({ '/',  loading_texture});
    loading_texture.loadFromFile("ressources/" + _where + "/lucky_block.png");
    _blockTextures.insert({ '?',  loading_texture});
    loading_texture.loadFromFile("ressources/" + _where + "/brick.png");
    _blockTextures.insert({ 'b',  loading_texture});
    loading_texture.loadFromFile("ressources/" + _where + "/floor.png");
    _blockTextures.insert({ 'x',  loading_texture});
    loading_texture.loadFromFile("ressources/" + _where + "/hard_block.png");
    _blockTextures.insert({ 'X',  loading_texture});
    loading_texture.loadFromFile("ressources/" + _where + "/pipe.png");
    _blockTextures.insert({ 'p',  loading_texture});
}

// -------------------| end init game |-------------------

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

void game::get_Size()
{
    int max = 0;
    int testing = 0;

    width = _map.size();
    for (std::size_t i = 0; i < _map.size(); i++) {
        for (std::size_t j = 0; j < _map[i].size(); j++)
            testing++;
        if (testing > max)
            max = testing;
        testing = 0;
    }
    length = max;
    return;
}

void game::createLine(const std::string &map_line, std::vector<sf::Vector2f> grid_line)
{
    for (std::size_t i = 0; i < map_line.size(); i++) {
        if (map_line[i] == ' ')
            continue;
        block *n_block = new block(grid_line[i], map_line[i], getTexture(map_line[i]), scale);
        lstBlock[grid_line[i].x / 16][grid_line[i].y / 16] = n_block;
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

void game::setScale(int ySize, int yNbElem)
{
    scale = ySize / yNbElem / 16;
}

sf::IntRect game::getPipeRect(int x, int y)
{
    int xSize = 0;
    int ySize = 0;
    if (lstBlock[x][y] == NULL)
        return {xSize, y, 0, 0};
    if (lstBlock[x][y]->getType() == '-') {
        ySize += 16;
        if (lstBlock[x][y - 1] != NULL && lstBlock[x][y - 1]->getType() == '-')
            xSize += 16;
    } else
        if (lstBlock[x + 1][y] != NULL && lstBlock[x + 1][y]->getType() == '|') {
            if (lstBlock[x - 1][y] != NULL && lstBlock[x - 1][y]->getType() == '-')
                 ySize += 32;
        }else
            xSize += 16;
    return {xSize, ySize, 16, 16};
}

void game::init_pipe()
{
    std::vector<char> pipeChar = {'|', '-', '<', '>', '_', '^'};
    for (int x = 0; x < lstBlock.size(); x++) {
        for (int y = 0; y < lstBlock[x].size(); y++) {
            if (lstBlock[x][y] != NULL &&
                (lstBlock[x][y]->getType() == '|' ||
                lstBlock[x][y]->getType() == '-' ||
                lstBlock[x][y]->getType() == '_' ||
                lstBlock[x][y]->getType() == '^')) {
                lstBlock[x][y]->setTexture(getTexture('p'), getPipeRect(x, y));
            }
        }
    }
}

void game::createLevel()
{
    std::size_t count = 0;
    int lvlHeight = 0;
    for (const auto &line : _map) {
        lvlHeight += 1;
        for (char c : line)
            if (c != ' ')
                count++;
    }
    setScale(_window->getSize().y, lvlHeight);
    createGrid(length);
    for (std::size_t i = 0; i < _map.size(); i++)
        createLine(_map[i], grid[i]);
    init_pipe();
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

void game::manageBlock()
{
    int animate = 0;
    if (animClock->actionNeed() == 1) // ça marche à moitié ça, tu regarderas, jsp
        animate = 1;
    for (std::size_t i = 0; i < lstBlock.size(); i++)
        for (std::size_t j = 0; j < lstBlock[i].size(); j++) {
            if (lstBlock[i][j] != NULL) {
                lstBlock[i][j]->draw(*_window);
                if (animate == 1)
                    lstBlock[i][j]->anime();
            }
        }
}

void game::loop()
{
    sf::Clock frames;

    while (_window->isOpen())
        if (frames.getElapsedTime().asMilliseconds() > (1.0f)/60*1000) {
            poll_event();
            _window->clear();
            manageBlock();
            _player->actualize(*_window);
            _window->display();
            frames.restart();
        }
}

// -------------------| game loop end |-------------------

sf::Texture game::getTexture(char c)
{
    if (c == 'a' || c == 's' || c == 'm' || c == 'f' || c == 'v')
        return _blockTextures['?'];
    if (_blockTextures.count(c)) {
        return  _blockTextures[c];
    } else {
        return _blockTextures['/'];
    }
}
