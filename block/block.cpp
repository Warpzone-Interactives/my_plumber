/*
** EPITECH PROJECT, 2025
** my_plumber
** File description:
** block.cpp
*/

#include "block.hpp"

block::block(sf::Vector2f position, char type, sf::Texture texture, float scale)
{
    _type = type;
    _position = position;
    _scale = int(scale);
    _position.x = (_position.x + 8) *_scale;
    _position.y = (_position.y + 8) *_scale;
    _direction = 0;
    _animated = false;
    _rect = sf::IntRect({0, 0}, {16, 16});
    _texture = texture;
    _sprite = sf::Sprite();
    _sprite.setTexture(_texture);
    _sprite.setTextureRect(_rect);
    _sprite.setPosition(_position);
    _sprite.setScale({_scale, _scale});
    _sprite.setOrigin({8, 8});
    if (type == '?' || type == 'a' || type == 's' ||
        type == 'm' || type == 'f' || type == 'v')
        initLuckyBlock(type);
}

void block::initLuckyBlock(char type)
{
    _animated = true;
    _direction = 1;
    if (type > 90 || type == '?')
        _nbAnime = 3;
    else
        _nbAnime = 1;
    if (type == '?' || type == '!')
        _loot = "coin";
    if (type == 'a' || type == 'A')
        _loot = "auto";
    if (type == 's' || type == 'S')
        _loot = "star";
    if (type == 'm' || type == 'M')
        _loot = "mushroom";
    if (type == 'f' || type == 'F')
        _loot = "flower";
    if (type == 'v' || type == 'V')
        _loot = "one_up";
    return;
}

void block::anime()
{
    if (_nbAnime > 1) {
        _rect.left += _direction * 16;
        if (_rect.left == (_nbAnime - 1) * 16 || _rect.left == 0)
            _direction *= -1;
        _sprite.setTextureRect(_rect);
    }
    return;
}

void block::draw(sf::RenderWindow &window)
{
    window.draw(_sprite);
    return;
}

void block::setTexture(sf::Texture newTexture, sf::IntRect nRect)
{
    _rect = nRect;
    _texture = newTexture;
    _sprite.setTexture(_texture);
    _sprite.setTextureRect(_rect);
}

char block::getType()
{
    return _type;
}

bool block::isAnimated()
{
    return _animated;
}

sf::Vector2f block::getPos()
{
    return _position;
}