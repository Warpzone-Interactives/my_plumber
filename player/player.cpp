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
    _runningFramesLeft = 0;
    _onGround = true;
    _facingRight = true;
    _skidding= false;
    _chooseTexture();
    _sprite = sf::Sprite(_texture);
    _sprite.setTextureRect(_rect);
    _sprite.setPosition(_position);
    _sprite.setOrigin({8, 8});
    _sprite_nb = 1;
}

sf::Vector2f player::getPos()
{
    return _position;
}

void player::_chooseTexture()
{
    std::string filePath = "ressources/player/" + _character + "/";
    
    if (_size == 0) {
        filePath += "small.png";
        _rect = sf::IntRect({0, 0}, {16, 16});
        _sprite.setOrigin({8, 8});
        _sprite.setTextureRect(_rect);
    }
    else if (_size == 1) {
        filePath += "big.png";
        _rect = sf::IntRect({0, 0}, {16, 32});
        _sprite.setOrigin({8, 24});
        _sprite.setTextureRect(_rect);
    }
    else if (_size == 2) {
        filePath += "fire.png";
        _rect = sf::IntRect({0, 0}, {16, 32});
        _sprite.setOrigin({8, 24});
        _sprite.setTextureRect(_rect);
    }
    _setTexture(filePath);
}

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
    //3 blocs + 7 pixels vers le haut
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
        _size = 0;
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
    //     if (_size == 2 && KeyPressed = "b") { 
    //         lancer une boule de feu  //ça pourrait être sa classe à part en soit, puisque "tout est classe"
    //     }
    // }

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
    if (_skidding == false) {
        if (player::_velocity.x > RELEASE_DECELERATION)
            player::_velocity.x -= RELEASE_DECELERATION;
        if (player::_velocity.x < -RELEASE_DECELERATION)
            player::_velocity.x += RELEASE_DECELERATION;
    }
    else {
        if (player::_velocity.x > SKIDDING_DECELERATION)
            player::_velocity.x -= SKIDDING_DECELERATION;
        if (player::_velocity.x < -SKIDDING_DECELERATION)
            player::_velocity.x += SKIDDING_DECELERATION;
    }
    if (-RELEASE_DECELERATION <= player::_velocity.x && player::_velocity.x <= RELEASE_DECELERATION)
        player::_velocity.x = 0;
}

void player::_updateMovementWalking(int direction)
{
    if (direction == -1)
        return player::_handleIdleInput();
    if (direction == 1) {
        if (player::_velocity.x >= -SKID_TURNAROUND_SPEED) {
            player::_velocity.x += WALKING_ACCELERATION;
            _skidding = false;
        }
        else {
            player::_velocity.x += SKIDDING_DECELERATION;
            _skidding = true;
        }
        if (player::_velocity.x > MAXIMUM_WALK_SPEED)
            player::_velocity.x = MAXIMUM_WALK_SPEED;
    }
    if (direction == 0) {
        if (player::_velocity.x <= SKID_TURNAROUND_SPEED) {
            player::_velocity.x -= WALKING_ACCELERATION;
            _skidding = false;
        }
        else {
            player::_velocity.x -= SKIDDING_DECELERATION;
            _skidding = true;
        }
        if (player::_velocity.x < -MAXIMUM_WALK_SPEED)
            player::_velocity.x = -MAXIMUM_WALK_SPEED;
    }
}

void player::_updateMovementRunning(int direction)
{
    if (direction == -1) {
        _runningFramesLeft = 0;
        return player::_handleIdleInput();
    }
    if (direction == 1) {
        if (player::_velocity.x >= -SKID_TURNAROUND_SPEED)
            player::_velocity.x += RUNNING_ACCELERATION;
        else {
            player::_velocity.x += SKIDDING_DECELERATION;
            _runningFramesLeft = 0;
        }
        if (player::_velocity.x > MAXIMUM_RUNNING_SPEED)
            player::_velocity.x = MAXIMUM_RUNNING_SPEED;
    }
    if (direction == 0) {
        if (player::_velocity.x <= SKID_TURNAROUND_SPEED)
            player::_velocity.x -= RUNNING_ACCELERATION;
        else
            player::_velocity.x -= SKIDDING_DECELERATION;
        if (player::_velocity.x < -MAXIMUM_RUNNING_SPEED)
            player::_velocity.x = -MAXIMUM_RUNNING_SPEED;
    }
} //actuellement mario "snap" à la walk speed directement quand il ne court plus (il ne ralentit pas progressivement).

void player::_handleInput()
{
    int direction = -1;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        _runningFramesLeft = 10;
    else if (_runningFramesLeft != 0)
        _runningFramesLeft--;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        direction = 0;
        _facingRight = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        direction = 1;
        _facingRight = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J) && _size == 1)
        player::sizeDown();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::G) && _size == 0)
        player::sizeUp();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::K) && _size == 2)
        player::sizeDown();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::H) && _size == 1)
        player::sizeUp();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::L) && _size == 0)
        player::sizeDown();

    if (_runningFramesLeft == 0)
        player::_updateMovementWalking(direction);
    else
        player::_updateMovementRunning(direction);
}

void player::actualize(sf::RenderWindow &window)
{
    player::_checkInvincibility();
    player::_handleInput();

    if (_velocity.x >= MINIMUM_WALK_VELOCITY || _velocity.x <= MINIMUM_WALK_VELOCITY) {
        _position += _velocity;
        if (_position.x < 36) {
            _position.x = 36;
            _velocity.x = 0;
        }
        _sprite.setPosition(_position);
    }

    if (!_facingRight)
        _sprite.setScale({-4, 4});
    else
        _sprite.setScale({4, 4});

    player::_draw(window);
}
