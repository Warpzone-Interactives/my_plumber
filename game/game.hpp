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
    game(char *map, sf::RenderWindow *window, player *player);
    ~game() = default;

    int getError();
    void createLevel();
    sf::Texture getTexture(char c);
    void loop();

    gameClock *animClock;
    int status;
    block *_block; // next for chained list
    sf::RenderWindow *_window;
    player *_player;

private:

    void key_event(sf::Event *event);
    void analyse_events(sf::Event *event);
    void poll_event();
    void loadMap(std::string filepath);
    int getWhere(std::string filepath);
    void setScale(int ySize, int yNbElem);
    void initTexture();
    void get_Size();
    void initLstBlock();
    void createElement(char c, sf::Vector2f square);
    void createLine(const std::string &map_line, std::vector<sf::Vector2f> grid_line);
    void createGrid(int x_size);

    int length;
    int width;
    float scale;
    std::string _where;
    std::vector<std::vector<block *>> lstBlock;
    std::vector<std::vector<sf::Vector2f>> grid;
    std::vector<std::string> _map;
    std::vector<sf::Sprite> _sprites;
    std::map<char, sf::Texture> _textures;
};

#endif