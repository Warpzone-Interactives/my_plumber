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
    _nbAnime = 1;
    _animated = false;
    _rect = sf::IntRect({0, 0}, {16, 16});
    _texture = texture;
    _sprite = sf::Sprite();
    _sprite.setTexture(_texture);
    _sprite.setTextureRect(_rect);
    _sprite.setPosition(_position);
    _sprite.setScale({_scale, _scale});
    _sprite.setOrigin({8, 8});
    leftHitBox = NULL;
    rightHitBox = NULL;
    topHitBox = NULL;
    bottomHitBox = NULL;
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

void block::anime(sf::IntRect *rect)
{
    if (_nbAnime > 1) {
        _rect = *rect;
        _sprite.setTextureRect(_rect);
    }
    return;
}

void block::draw(sf::RenderWindow &window, int debug)
{
    window.draw(_sprite);
    if (debug == 1) {
        if (leftHitBox != NULL)
            window.draw(*leftHitBox);
        if (rightHitBox != NULL)
            window.draw(*rightHitBox);
        if (topHitBox != NULL)
            window.draw(*topHitBox);
        if (bottomHitBox != NULL)
            window.draw(*bottomHitBox);
    }
    return;
}

void block::setRect(sf::IntRect rect)
{
    _rect = rect;
    _sprite.setTextureRect(_rect);
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
        leftHitBox = new sf::RectangleShape({2 * _scale, 16 * _scale});
        leftHitBox->setOrigin({1 * _scale, 8 * _scale});
        leftHitBox->setPosition({_position.x - 8 * _scale, _position.y});
        leftHitBox->setFillColor(sf::Color::Transparent);
        leftHitBox->setOutlineThickness(1);
        leftHitBox->setOutlineColor(sf::Color::Blue);
    }
    if (right == 1) {
        rightHitBox = new sf::RectangleShape({2 * _scale, 16 * _scale});
        rightHitBox->setOrigin({1 * _scale, 8 * _scale});
        rightHitBox->setPosition({_position.x + 8 * _scale, _position.y});
        rightHitBox->setFillColor(sf::Color::Transparent);
        rightHitBox->setOutlineThickness(1);
        rightHitBox->setOutlineColor(sf::Color::Green);
    }
    if (top == 1) {
        topHitBox = new sf::RectangleShape({16 * _scale, 4 * _scale});
        topHitBox->setOrigin({8 * _scale, 1 * _scale});
        topHitBox->setPosition({_position.x, _position.y - 6 * _scale});
        topHitBox->setFillColor(sf::Color::Transparent);
        topHitBox->setOutlineThickness(1);
        topHitBox->setOutlineColor(sf::Color::Red);
    }
    if (bottom == 1) {
        bottomHitBox = new sf::RectangleShape({16 * _scale, 2 * _scale});
        bottomHitBox->setOrigin({8 * _scale, 1 * _scale});
        bottomHitBox->setPosition({_position.x, _position.y + 8 * _scale});
        bottomHitBox->setFillColor(sf::Color::Transparent);
        bottomHitBox->setOutlineThickness(1);
        bottomHitBox->setOutlineColor(sf::Color::Yellow);
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