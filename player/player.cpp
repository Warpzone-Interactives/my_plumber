/*
** EPITECH PROJECT, 2025
** my_plumber
** File description:
** my.hpp
*/

#include "player.hpp"

player::player(int size, sf::Vector2f position, char m)
{
    _size = size;
    _position = position;
    if (m == 'm')
        character = "mario";
    else
        character = "luigi";
    _alive = true;
    _invincible = false;
    _invincibilityDuration = 0.0f;
    _velocity = sf::Vector2f(0.0f, 0.0f);
    _onGround = true;
    _facingRight = true;
    _chooseTexture();
    _sprite = sf::Sprite(_texture);
    _sprite.setPosition(_position);
}

void player::_chooseTexture()
{
    std::string filePath = "player/" + character + "/";

    if (_size == 0)
        filePath += "small.png";
    else if (_size == 1)
        filePath += "big.png";
    else if (_size == 2)
        filePath += "fire.png";
    _setTexture(filePath);
} // En théorie ça devrait marcher mais du coup faut setup les intRect aussi je crois ?? jsp :/

void player::_setTexture(std::string filepath)
{
    _texture = sf::Texture();
    _texture.loadFromFile(filepath);
    _sprite.setTexture(_texture);
}

void player::_kill()
{
    _alive = false;
    // _playDeathAnimation(); ??
}

void player::draw(sf::RenderWindow &window)
{
    window.draw(_sprite);
}

void player::sizeUp()
{
    if (_size < 2)
        _size++;
    //powerup_animation ?
    _chooseTexture();
}

void player::sizeDown()
{
    if (_size > 0)
        _size--;
    else
        return _kill();
    //dmg_animation ?
    _invincible = true;
    _chooseTexture();
} // https://youtube.com/clip/UgkxKB8VUWV1k7F8slDmzFQhL8ufuSxesyAu?si=4pkCQniZGHPhfBQH

void player::giveStar()
{
    _invincible = true;
    _invincibilityDuration = 12.0f; // 400 sec timer = 160 sec et star dure 30 sec timer donc 12 sec
    _invincibilityClock.restart();
    //if (!invincibility music) play it
    //same pour l'anim
} // https://youtube.com/clip/UgkxPNQt56KE723coeqs2zg6gfIu32_fpotV?si=Dz7iicDGEC9WFhqu

// void player::shoot()
// {
//     if (_size == 2 && KeyPressed = "b") { // sfEvent ? 
//         lancer une boule de feu  //ça pourrait être sa classe à part en soit, puisque "tout est classe"
//     }
// }