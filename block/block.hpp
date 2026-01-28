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
    block(sf::Vector2f position, char type, sf::Texture texture, block *next);
    ~block() = default;

    void anime();
    void try_break();
    void draw(sf::RenderWindow &window);

    char _type;
    block *_next; // next for chained list

private:

    int _nb_anim; // nb animation frame
    std::string loot; // what in (power up, cion)
    bool _can_break; // if is breacable block
    sf::Vector2f _position; // Position

    sf::IntRect _rect; // rect for texture
    sf::Texture _texture; //texture
    sf::Sprite _sprite; //sprite
};

#endif
