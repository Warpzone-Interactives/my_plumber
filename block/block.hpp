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
    block(sf::Vector2f position, char type, sf::Texture texture, float scale);
    ~block() = default;

    void initLuckyBlock(char type); //je peut la mettre en privé
    void anime();
    void try_break();
    void draw(sf::RenderWindow &window);
    char getType();
    void setTexture(sf::Texture newTexture, sf::IntRect nRect);
    bool isAnimated();
    sf::Vector2f getPos();


private:

    char _type;
    sf::Sprite _sprite; //sprite
    int _nbAnime; // nb animation frame
    bool _animated; // if is animated
    int _direction; // how chosse next sprite
    std::string _loot; // what in (power up, cion)
    bool _canBreak; // if is breacable block
    sf::Vector2f _position; // Position
    float _scale;

    sf::IntRect _rect; // rect for texture
    sf::Texture _texture; //texture
};

#endif
