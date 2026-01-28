/*
** EPITECH PROJECT, 2025
** my_plumber
** File description:
** block.cpp
*/

#include "block.hpp"

block::block(sf::Vector2f position, char type, sf::Texture texture, block *next)
{
    _type = type;
    _position = position;
    _rect = sf::IntRect({0, 0}, {16, 16});
    _texture = texture;
    _sprite = sf::Sprite();
    _sprite.setTexture(_texture);
    _sprite.setTextureRect(_rect);
    _sprite.setPosition(_position);
    _next = next;
}

void block::draw(sf::RenderWindow &window)
{
    window.draw(_sprite);
    if (block::_next != NULL)
        block::_next->draw(window);
}