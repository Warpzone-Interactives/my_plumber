/*
** EPITECH PROJECT, 2025
** my_plumber
** File description:
** block.cpp
*/

#include "block.hpp"

block::block(sf::Vector2f position, char type, sf::Texture texture, block *next, int scale)
{
    _type = type;
    _position = position;
    _scale = scale;
    _position.y *= scale;
    _position.x *= scale;
    _nbAnime = 1;
    _rect = sf::IntRect({0, 0}, {16, 16});
    _texture = texture;
    _sprite = sf::Sprite();
    _sprite.setTexture(_texture);
    _sprite.setTextureRect(_rect);
    _sprite.setPosition(_position);
    _sprite.setScale({_scale, _scale});
    _next = next;
    if (type == '?' || type == 'a' || type == 's' ||
        type == 'm' || type == 'f' || type == 'v')
        initLuckyBlock(type);
}

void block::initLuckyBlock(char type)
{
    if (type > 90 || type == '?')
        _nbAnime = 3;
    else
        _nbAnime = 1;
    if (type == '?' || type == '!')
        loot = "coin";
    if (type == 'a' || type == 'A')
        loot = "auto";
    if (type == 's' || type == 'S')
        loot = "star";
    if (type == 'm' || type == 'M')
        loot = "mushroom";
    if (type == 'f' || type == 'F')
        loot = "flower";
    if (type == 'v' || type == 'V')
        loot = "one_up";
    return;
}

void block::anime()
{
    if (_nbAnime > 1) {
        _rect.left += 16;
        if (_rect.left == _nbAnime * 16)
            _rect.left = 0;
        _sprite.setTextureRect(_rect);
    }
    if (block::_next != NULL)
        block::_next->anime();
    return;
}

void block::draw(sf::RenderWindow &window)
{
    window.draw(_sprite);
    if (block::_next != NULL)
        block::_next->draw(window);
    return;
}