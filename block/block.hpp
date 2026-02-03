/*
** EPITECH PROJECT, 2025
** my_plumber
** File description:
** my.hpp
*/

#include "my.hpp"

#ifndef BLOCK_HPP
    #define BLOCK_HPP

class block
{
public:
    block(sf::Vector2f position, char type, sf::Texture texture, block *next, float scale);
    ~block() = default;

    void initLuckyBlock(char type); //je peut la mettre en privé
    void anime();
    void try_break();
    void draw(sf::RenderWindow &window);

    char _type;
    block *_next; // next for chained list

private:

    int _nbAnime; // nb animation frame
    std::string loot; // what in (power up, cion)
    bool _can_break; // if is breacable block
    sf::Vector2f _position; // Position
    float _scale;

    sf::IntRect _rect; // rect for texture
    sf::Texture _texture; //texture
    sf::Sprite _sprite; //sprite
};

#endif
