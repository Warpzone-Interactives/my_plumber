/*
** EPITECH PROJECT, 2025
** my_plumber
** File description:
** my.hpp
*/

#include "my.hpp"

#ifndef GENERAL_HPP
    #define GENERAL_HPP

class game
{
public:
    game(char *map, sf::RenderWindow *window, player *player, sf::View *view);
    ~game() = default;

    int getError();
    void initLevel();
    sf::Texture getTexture(char c);
    void loop();

    gameClock *animClock;
    int status;
    sf::View *camera;
    sf::RenderWindow *_window;
    player *_player;

private:

    // ---| game lauched |---
    void manageBlock();
    void key_event(sf::Event *event);
    void analyse_events(sf::Event *event);
    void poll_event();

    // ---| init map |---
    void get_Size();
    void createLine(const std::string &map_line, std::vector<sf::Vector2f> grid_line);
    void createGrid(int x_size);
    void setScale(int ySize, int yNbElem);
    sf::IntRect getPipeRect(int x, int y);
    sf::IntRect getVerticalPipeRect(int x, int y);
    void initPipe();
    void initHitBox();

    // ---| init game |---
    void initLstBlock();
    int getWhere(std::string filepath);
    void loadMap(std::string filepath);
    void initBlockTexture();

    // ---| loop game |---
    void anime();

    sf::IntRect _rect; // rect for texture
    std::map<char, sf::Texture> _textures;
    std::vector<std::vector<block *>> lstBlock;
    int _direction; // how chosse next sprite

    int _debug;
    int length;
    int width;
    float scale;
    std::string _where;
    std::vector<std::vector<sf::Vector2f>> grid;
    std::vector<std::string> _map;
    std::vector<sf::Sprite> _sprites;
    std::map<char, sf::Texture> _blockTextures;
    sf::RectangleShape _backGround;
};

#endif