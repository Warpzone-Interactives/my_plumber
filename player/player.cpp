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
        _character = "mario";
    else
        _character = "luigi";
    _alive = true;
    _invincible = false;
    _invincibilityDuration = 0.0f;
    _velocity = sf::Vector2f(0.0f, 0.0f);
    _onGround = true;
    _facingRight = true;
    _running = false;
    _chooseTexture();
    _rect = sf::IntRect({0, 0}, {16, 16});
    _sprite = sf::Sprite(_texture);
    _sprite.setTextureRect(_rect);
    _sprite.setPosition(_position);
    _sprite.setOrigin({8, 8});
}

void player::_checkInvincibility()
{
    if (_invincible) {
        if (_invincibilityClock.getElapsedTime().asSeconds() > _invincibilityDuration) {
            _invincible = false;
            _invincibilityDuration = 0.0f;
        }
    }
}


void player::_handleIdleInput()
{
    if (player::_velocity.x > RELEASE_DECELERATION)
        player::_velocity.x -= RELEASE_DECELERATION;
    if (player::_velocity.x < -RELEASE_DECELERATION)
        player::_velocity.x += RELEASE_DECELERATION;
    if (-RELEASE_DECELERATION <= player::_velocity.x && player::_velocity.x <= RELEASE_DECELERATION)
        player::_velocity.x = 0;
} //On suppose ici qu'il y a pas de skidding (cf _updateMovement)

void player::_updateMovement(int direction)
{
    if (direction == -1)
        return player::_handleIdleInput();
    if (direction == 1) {
        if (player::_velocity.x >= 0)
            player::_velocity.x += WALKING_ACCELERATION;
        else
            player::_velocity.x += SKIDDING_DECELERATION;
        if (player::_velocity.x > MAXIMUM_WALK_SPEED)
            player::_velocity.x = MAXIMUM_WALK_SPEED;
    }
    if (direction == 0) {
        if (player::_velocity.x <= 0)
            player::_velocity.x -= WALKING_ACCELERATION; //on va vers la gauche
        else
            player::_velocity.x -= SKIDDING_DECELERATION; //on ralentit en appuyant sur gauche
        if (player::_velocity.x < -MAXIMUM_WALK_SPEED)
            player::_velocity.x = -MAXIMUM_WALK_SPEED; //on vérifie qu'on dépasse pas le max
    }
} //dans l'idée ça "passe" mais y'a encore des trucs à faire comme le skidding à gérer (tant que y'a pas
  //un autre input mario continue de skid) (aussi skid turnaround speed à implémenter)
  //Ah et la course aussi est pas implémentée 

void player::_handleInput()
{
    int direction = -1;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        direction = 0;
        _facingRight = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        direction = 1;
        _facingRight = true;
    }
    player::_updateMovement(direction);
}

void player::actualize(sf::RenderWindow &window)
{
    player::_checkInvincibility();
    player::_handleInput();
    if (player::_velocity.x >= MINIMUM_WALK_VELOCITY || player::_velocity.x <= MINIMUM_WALK_VELOCITY) {
        player::_position += player::_velocity;
        player::_sprite.setPosition(player::_position);
    }
    if (!player::_facingRight)
        player::_sprite.setScale({-1, 1});
    else
        player::_sprite.setScale({1, 1});
    player::_draw(window);
}

void player::_chooseTexture()
{
    std::string filePath = "ressources/player/" + _character + "/";

    if (_size == 0)
        filePath += "small.png";
    else if (_size == 1)
        filePath += "big.png";
    else if (_size == 2)
        filePath += "fire.png";
    _setTexture(filePath);
} // En théorie ça devrait marcher mais du coup faut setup les intRect aussi je crois ??

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

void player::_draw(sf::RenderWindow &window)
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