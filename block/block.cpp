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
    _leftHitBox = NULL;
    _rightHitBox = NULL;
    _topHitBox = NULL;
    _bottomHitBox = NULL;
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

void block::draw(sf::RenderWindow &window, int debug)
{
    window.draw(_sprite);
    if (debug == 1) {
        if (_leftHitBox != NULL)
            window.draw(*_leftHitBox);
        if (_rightHitBox != NULL)
            window.draw(*_rightHitBox);
        if (_topHitBox != NULL)
            window.draw(*_topHitBox);
        if (_bottomHitBox != NULL)
            window.draw(*_bottomHitBox);
    }
    return;
}

void block::setTexture(sf::Texture newTexture, sf::IntRect nRect)
{
    _rect = nRect;
    _texture = newTexture;
    _sprite.setTexture(_texture);
    _sprite.setTextureRect(_rect);
}

void block::setHitBox(int left, int right, int top, int bottom)
{
    if (left == 1) {
        _leftHitBox = new sf::RectangleShape({2 * _scale, 16 * _scale});
        _leftHitBox->setOrigin({1 * _scale, 8 * _scale});
        _leftHitBox->setPosition({_position.x - 8 * _scale, _position.y});
        _leftHitBox->setFillColor(sf::Color::Transparent);
        _leftHitBox->setOutlineThickness(1);
        _leftHitBox->setOutlineColor(sf::Color::Blue);
    }
    if (right == 1) {
        _rightHitBox = new sf::RectangleShape({2 * _scale, 16 * _scale});
        _rightHitBox->setOrigin({1 * _scale, 8 * _scale});
        _rightHitBox->setPosition({_position.x + 8 * _scale, _position.y});
        _rightHitBox->setFillColor(sf::Color::Transparent);
        _rightHitBox->setOutlineThickness(1);
        _rightHitBox->setOutlineColor(sf::Color::Green);
    }
    if (top == 1) {
        _topHitBox = new sf::RectangleShape({16 * _scale, 2 * _scale});
        _topHitBox->setOrigin({8 * _scale, 1 * _scale});
        _topHitBox->setPosition({_position.x, _position.y - 8 * _scale});
        _topHitBox->setFillColor(sf::Color::Transparent);
        _topHitBox->setOutlineThickness(1);
        _topHitBox->setOutlineColor(sf::Color::Red);
    }
    if (bottom == 1) {
        _bottomHitBox = new sf::RectangleShape({16 * _scale, 2 * _scale});
        _bottomHitBox->setOrigin({8 * _scale, 1 * _scale});
        _bottomHitBox->setPosition({_position.x, _position.y + 8 * _scale});
        _bottomHitBox->setFillColor(sf::Color::Transparent);
        _bottomHitBox->setOutlineThickness(1);
        _bottomHitBox->setOutlineColor(sf::Color::Yellow);
    }
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