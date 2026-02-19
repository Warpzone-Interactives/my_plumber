/*
** EPITECH PROJECT, 2025
** my_plumber
** File description:
** rectangleShapes for blocks
*/

#include "rect.hpp"

rect::rect(char attribut, sf::Vector2f position, float scale)
{
    sf::Vector2f size;
    sf::Color color;

    if (attribut == 'w') {
        size = {16, 15.8};
        color = sf::Color::Yellow;
    } else {
        size = {15.8, 16};
        color = sf::Color::Green;
    }

    _type = attribut;    

    _rectangle = sf::RectangleShape(size);
    _rectangle.setOutlineColor(color);
    _rectangle.setOutlineThickness(0.1f);
    _rectangle.setFillColor(sf::Color::Transparent);
    _rectangle.setScale({scale, scale});
    _rectangle.setPosition({(position.x + 8) * scale, (position.y + 8) * scale});
    _rectangle.setOrigin({8, 8});
}

char rect::getType()
{
    return _type;
}

sf::RectangleShape rect::getRect()
{
    return _rectangle;
}

void rect::draw(sf::RenderWindow &window)
{
    window.draw(_rectangle);
}
