/*
** EPITECH PROJECT, 2025
** my_plumber
** File description:
** init_general
*/

#include "game.hpp"

// -------------------| init game |-------------------

game::game(char *filepath, sf::RenderWindow *window, sf::View *view, player *player1, player *player2)
{
    _player1 = player1;
    _player2 = player2;
    _window = window;
    _window->setFramerateLimit(60);
    camera = view;
    window->setView(*camera);
    window->setMouseCursorVisible(false);

    _debugFont.loadFromFile("ressources/debugFont.ttf");
    _debugStr.insert(0, "Debug Mod = True");
    _debugInfo.setFont(_debugFont);
    _debugInfo.setString(_debugStr);
    _debugInfo.setCharacterSize(30);
    _debugInfo.setFillColor(sf::Color::White);
    _debugInfo.setOutlineColor(sf::Color::Black);
    _debugInfo.setOutlineThickness(0.5);
    _debugInfo.setPosition({camera->getCenter().x + (camera->getSize().x / 4), camera->getCenter().y - (camera->getSize().y / 2)});

    animClock = new gameClock({1, 0.25, 0.25, 0.25});
    _rect = sf::IntRect({0, 0}, {16, 16});

    sf::RectangleShape bg(camera->getSize());
    _backGround = bg;
    _backGround.setOrigin(_backGround.getSize().x / 2, _backGround.getSize().y / 2);
    _backGround.setPosition(camera->getCenter());
    _backGround.setFillColor(sf::Color(148, 148, 255, 255));

    status = 0;
    _scale = 1;
    _direction = 1;
    if (getWhere(filepath) == 1)
        status += 1;
    _debug = -1;

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

// -------------------| pipe part |-------------------

sf::IntRect game::getVerticalPipeRect(int x, int y)
{
    int xSize = 0;
    int ySize = 0;
    if ((x + 1 < lstBlock.size()) && lstBlock[x + 1][y] != NULL && lstBlock[x + 1][y]->getType() == '|') // si a droite c'est un pipe Vertical
    {
        if ((x > 0) && lstBlock[x - 1][y] != NULL &&
            (lstBlock[x - 1][y]->getType() == '-' || // si a droite c'est un pipe horizontal
             lstBlock[x - 1][y]->getType() == '<'))  // ou une sortie
        {
            ySize += 32;
            if ((y > 0) && lstBlock[x - 1][y - 1] != NULL &&
                (lstBlock[x - 1][y - 1]->getType() == '-' || // si c'est la partie du bas ou pas
                 lstBlock[x - 1][y - 1]->getType() == '<'))
                ySize += 16;
        }
    }
    else
    {
        if ((x + 1 < lstBlock.size()) && lstBlock[x + 1][y] != NULL &&
            (lstBlock[x + 1][y]->getType() == '-' ||
             lstBlock[x + 1][y]->getType() == '>'))
        {
            ySize += 32;
            if ((y > 0) && lstBlock[x + 1][y - 1] != NULL &&
                (lstBlock[x + 1][y - 1]->getType() == '-' ||
                 lstBlock[x + 1][y - 1]->getType() == '>'))
                ySize += 16;
        }
        xSize += 16;
    }
    return {xSize, ySize, 16, 16};
}

sf::IntRect game::getPipeRect(int x, int y)
{
    int xSize = 0;
    int ySize = 0;
    if (lstBlock[x][y] == NULL)
        return {xSize, y, 0, 0};
    if (lstBlock[x][y]->getType() == '-') { // si tuyaux horizontal
        ySize += 16;
        if ((y > 0) && lstBlock[x][y - 1] != NULL && lstBlock[x][y - 1]->getType() == '-') // si au dessus c'est un tuyaux vertical
            xSize += 16;
        return {xSize, ySize, 16, 16};
    } else {                                 // sinon tyaux vertical
        return getVerticalPipeRect(x, y);
    }
    return {xSize, ySize, 16, 16};
}

void game::init_pipe()
{
    for (int x = 0; x < lstBlock.size(); x++) {
        for (int y = 0; y < lstBlock[x].size(); y++) {
            if (lstBlock[x][y] != NULL &&
                (lstBlock[x][y]->getType() == '|' ||
                lstBlock[x][y]->getType() == '-')) {
                lstBlock[x][y]->setTexture(getTexture('p'), getPipeRect(x, y));
            }
        }
    }
}

// -------------------| init map |-------------------
// -------------------| end pipe part |-------------------


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
        block *n_block = new block(grid_line[i], map_line[i], getTexture(map_line[i]), _scale);
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
    _scale = ySize / yNbElem / 16;
}

// -------------------| init map |-------------------
// -------------------| pipe part |-------------------

sf::IntRect game::getVerticalPipeRect(int x, int y)
{
    int xSize = 0;
    int ySize = 0;
    if ((x + 1 < lstBlock.size()) && lstBlock[x + 1][y] != NULL && lstBlock[x + 1][y]->getType() == '|') // si a droite c'est un pipe Vertical
    {
        if ((x > 0) && lstBlock[x - 1][y] != NULL &&
            (lstBlock[x - 1][y]->getType() == '-' || // si a droite c'est un pipe horizontal
             lstBlock[x - 1][y]->getType() == '<'))  // ou une sortie
        {
            ySize += 32;
            if ((y > 0) && lstBlock[x - 1][y - 1] != NULL &&
                (lstBlock[x - 1][y - 1]->getType() == '-' || // si c'est la partie du bas ou pas
                 lstBlock[x - 1][y - 1]->getType() == '<'))
                ySize += 16;
        }
    }
    else
    {
        if ((x + 1 < lstBlock.size()) && lstBlock[x + 1][y] != NULL &&
            (lstBlock[x + 1][y]->getType() == '-' ||
             lstBlock[x + 1][y]->getType() == '>'))
        {
            ySize += 32;
            if ((y > 0) && lstBlock[x + 1][y - 1] != NULL &&
                (lstBlock[x + 1][y - 1]->getType() == '-' ||
                 lstBlock[x + 1][y - 1]->getType() == '>'))
                ySize += 16;
        }
        xSize += 16;
    }
    return {xSize, ySize, 16, 16};
}

sf::IntRect game::getPipeRect(int x, int y)
{
    int xSize = 0;
    int ySize = 0;
    if (lstBlock[x][y] == NULL)
        return {xSize, y, 0, 0};
    if (lstBlock[x][y]->getType() == '-') { // si tuyaux horizontal
        ySize += 16;
        if ((y > 0) && lstBlock[x][y - 1] != NULL && lstBlock[x][y - 1]->getType() == '-') // si au dessus c'est un tuyaux vertical
            xSize += 16;
        return {xSize, ySize, 16, 16};
    } else {                                 // sinon tyaux vertical
        return getVerticalPipeRect(x, y);
    }
    return {xSize, ySize, 16, 16};
}

void game::initPipe()
{
    for (int x = 0; x < lstBlock.size(); x++) {
        for (int y = 0; y < lstBlock[x].size(); y++) {
            if (lstBlock[x][y] != NULL &&
                (lstBlock[x][y]->getType() == '|' ||
                lstBlock[x][y]->getType() == '-')) {
                lstBlock[x][y]->setTexture(getTexture('p'), getPipeRect(x, y));
            }
        }
    }
}

// -------------------| end pipe part |-------------------
// -------------------| init HitBox |-------------------

void game::initHitBox()
{
    int left = 0;
    int right = 0;
    int top = 0;
    int bottom = 0;
    for (int x = 0; x < lstBlock.size(); x++) {
        for (int y = 0; y < lstBlock[x].size(); y++) {
            if (lstBlock[x][y] != NULL) {
                if(x > 0 && lstBlock[x - 1][y] == NULL)
                    left = 1;
                if(x < length - 1 && lstBlock[x + 1][y] == NULL)
                    right = 1;
                if(y > 0 && lstBlock[x][y - 1] == NULL)
                    top = 1;
                if(y < lstBlock[x].size() - 1 && lstBlock[x][y + 1] == NULL)
                    bottom = 1;
                lstBlock[x][y]->setHitBox(left, right, top, bottom);
                left = 0;
                right = 0;
                top = 0;
                bottom = 0;
            }
        }
    } 
}

// -------------------| end init HitBox |-------------------
// -------------------| init map |-------------------

void game::initLevel()
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
    _player1->setScale(_scale);
    if (_player2 != NULL)
        _player2->setScale(_scale);
    createGrid(length);
    for (std::size_t i = 0; i < _map.size(); i++)
        createLine(_map[i], grid[i]);
    initPipe();
    initHitBox();
}

// -------------------| init map end |-------------------

// -------------------| game loop |-------------------

void game::debugMod()
{
    _debug *= -1;
    if (_debug == 1) {
        _window->setMouseCursorVisible(true);
    } else {
        _window->setMouseCursorVisible(false);
    }
}

void game::key_event(sf::Event *event)
{
    switch (event->key.code) {
        case sf::Keyboard::Escape:
            _window->close();
            break;
        case sf::Keyboard::F3:
            debugMod();
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
    if (animClock->actionNeed(0) == 1) {
        anime();
        animate = 1;
    }
    for (std::size_t i = int((camera->getCenter().x - (camera->getSize().x / 2)) / (16 * _scale));
        i < lstBlock.size() && i < int(1 + (camera->getCenter().x + (camera->getSize().x / 2)) / (16 * _scale)); i++)
        for (std::size_t j = 0; j < lstBlock[i].size(); j++)
            if (lstBlock[i][j] != NULL) {
                lstBlock[i][j]->draw(*_window, _debug);
                if (lstBlock[i][j]->isAnimated() && animate == 1)
                    lstBlock[i][j]->setRect(_rect);
            }
}

void game::anime()
{
    _rect.left += _direction * 16;
    if (_rect.left == 32 || _rect.left == 0)
        _direction *= -1;
    return;
}

void game::manageDebugMod()
{
    if (_debug == 1) {
        _debugStr.clear();
        std::string str = "Debug Mod =\ttrue\n";
        str += "player type = \t" + _player1->getChar() + "\n";
        str += "player size = \t" + _player1->getSize() + "\n";
        str += "player facing = \t" + _player1->getFacing() + "\n";
        str += "player on Ground = \t" + _player1->getOnGround() + "\n";
        str += "player is Alive = \t" + _player1->getAlive() + "\n";
        str += "Player x pos =\t" + std::to_string(_player1->getPos().x / (_scale * 16) - 0.5) + "\n";
        str += "Player y pos =\t" + std::to_string(_player1->getPos().y / (_scale * 16) - 0.5) + "\n";
        str += "Player x vel =\t" + std::to_string(_player1->getVel().x / _scale) + "\n";
        str += "Player y vel =\t" + std::to_string(_player1->getVel().y / _scale) + "\n";
        _debugStr.insert(0, str);
        _debugInfo.setString(_debugStr);
        _window->draw(_debugInfo);
    }
}

void game::loop()
{
    sf::Clock frames;

    while (_window->isOpen())
        if (frames.getElapsedTime().asMilliseconds() > (1.0f)/60*1000) {
            poll_event();
            _window->clear();
            _window->draw(_backGround);
            manageBlock();
            _player1->actualize(*_window, camera, lstBlock);
            if (_player2 != NULL)
                _player2->actualize(*_window, camera, lstBlock);
            manageDebugMod();
            _window->display();
            if (camera->getCenter().x < _player1->getPos().x) {
                camera->setCenter(_player1->getPos().x, _window->getSize().y / 2);
                _window->setView(*camera);
                _debugInfo.setPosition({camera->getCenter().x + (camera->getSize().x / 4), camera->getCenter().y - (camera->getSize().y / 2)});
                _backGround.setPosition(camera->getCenter());
            }
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
