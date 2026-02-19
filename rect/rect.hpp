/*
** EPITECH PROJECT, 2025
** my_plumber
** File description:
** rect.hpp
*/

#include "my.hpp"

#ifndef RECT_HPP
    #define RECT_HPP

class rect
{
public:
    rect(char attribut, sf::Vector2f position, float scale);
    ~rect() = default;

    sf::RectangleShape getRect();
    void draw(sf::RenderWindow &window);
    char getType();

private:
    sf::RectangleShape _rectangle;
    char _type;
};

#endif
