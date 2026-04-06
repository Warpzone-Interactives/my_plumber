/*
** EPITECH PROJECT, 2025
** my_plumber
** File description:
** my.hpp
*/

#include "my.hpp"

#ifndef GENERAL_HPP
    #define GENERAL_HPP

class entity;
class player;
class block;
class gameClock;

class game
{
public:
    game(char *filepath, sf::RenderWindow *window, sf::View *view);
    ~game() = default;

    int getError();
    void initLevel();
    sf::Texture getTexture(char c);
    void loop();
    std::vector<std::vector<block*>> getMap();
    int getDebug();

    gameClock *animClock;
    int status;
    sf::View *camera;
    sf::RenderWindow *_window;
    player *_player1;
    player *_player2;
    entity *_enemy;

private:

    // ---| game lauched |---
    void manageBlock();
    void key_event(sf::Event *event);
    void analyse_events(sf::Event *event);
    void poll_event();
    void debugMod();
    void manageDebugMod();
    void anime();
    void actualized_camera();

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

    sf::IntRect _rect; // rect for texture
    std::map<char, sf::Texture> _textures;
    std::vector<std::vector<block *>> _lstBlock;
    int _direction; // how chosse next sprite

    int length;
    int width;
    float _scale;
    std::string _where;
    std::vector<std::vector<sf::Vector2f>> grid;
    std::vector<std::string> _map;
    std::vector<sf::Sprite> _sprites;
    std::map<char, sf::Texture> _blockTextures;

    int _debug;
    sf::String _debugStr;
    sf::Font _debugFont;
    sf::Text _debugInfo;
    sf::RectangleShape _backGround;
};

#endif