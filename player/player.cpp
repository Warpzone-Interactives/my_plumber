/*
** EPITECH PROJECT, 2025
** my_plumber
** File description:
** my.hpp
*/

#include "player.hpp"

player::player(int size, sf::Vector2f position, char m, int scale)
{
    _size = size;
    _position = position;
    if (m == 'm')
        _character = "mario";
    if (m == 'l')
        _character = "luigi";
    if (m == 'w')
        _character = "wario";
    _scale = scale;
    _alive = true;
    _invincible = false;
    _invincibilityDuration = 0.0f;
    _velocity = sf::Vector2f(0.0f, 0.0f);
    _runningFramesLeft = 0;
    _onGround = true;
    _facingRight = true;
    _skidding= false;
    _chooseTexture();
    _animated = 0;
    _animClock = new gameClock({0.125});
    _sprite_nb = 1;
    setHitBox();
}

void player::setHitBox()
{
    printf("pos x/y = %.2f/%.2f sclale = %.2f\n", _position.x, _position.y, _scale);
        _leftHitBox = new sf::RectangleShape({2 * _scale, 16 * _scale});
        _leftHitBox->setOrigin({1 * _scale, 8 * _scale});
        _leftHitBox->setPosition({_position.x - 8 * _scale, _position.y});
        _leftHitBox->setFillColor(sf::Color::Transparent);
        _leftHitBox->setOutlineThickness(1);
        _leftHitBox->setOutlineColor(sf::Color::Blue);

        _rightHitBox = new sf::RectangleShape({2 * _scale, 16 * _scale});
        _rightHitBox->setOrigin({1 * _scale, 8 * _scale});
        _rightHitBox->setPosition({_position.x + 8 * _scale, _position.y});
        _rightHitBox->setFillColor(sf::Color::Transparent);
        _rightHitBox->setOutlineThickness(1);
        _rightHitBox->setOutlineColor(sf::Color::Green);

        _topHitBox = new sf::RectangleShape({16 * _scale, 2 * _scale});
        _topHitBox->setOrigin({8 * _scale, 1 * _scale});
        _topHitBox->setPosition({_position.x, _position.y - 8 * _scale});
        _topHitBox->setFillColor(sf::Color::Transparent);
        _topHitBox->setOutlineThickness(1);
        _topHitBox->setOutlineColor(sf::Color::Red);

        _bottomHitBox = new sf::RectangleShape({16 * _scale, 2 * _scale});
        _bottomHitBox->setOrigin({8 * _scale, 1 * _scale});
        _bottomHitBox->setPosition({_position.x, _position.y + 8 * _scale});
        _bottomHitBox->setFillColor(sf::Color::Transparent);
        _bottomHitBox->setOutlineThickness(1);
        _bottomHitBox->setOutlineColor(sf::Color::Yellow);

}

void player::setScale(int scale)
{
    _scale = scale;
}

sf::Vector2f player::getPos()
{
    return _position;
}

sf::Vector2f player::getVel()
{
    return _velocity;
}

std::string player::getChar()
{
    return _character;
}

std::string player::getSize()
{
    if (_size == 1)
        return "Small";
    if (_size == 2)
        return "Big";
    if (_size == 3)
        return "Fire";
    return "Unknow";
}

std::string player::getFacing()
{
    if (_facingRight == true)
        return "right";
    return "left";
}

std::string player::getOnGround()
{
    if (_onGround)
        return "true";
    return "false";
}

std::string player::getAlive()
{
    if (_alive)
        return "true";
    return "false";
}



void player::_chooseTexture()
{
    std::string filePath = "ressources/player/" + _character + "/";
    
    if (_size == 0) {
        filePath += "small.png";
        _texture_rect = sf::IntRect({0, 0}, {16, 16});
        _sprite.setOrigin({8, 8});
        _sprite.setTextureRect(_texture_rect);
    }
    else if (_size == 1) {
        filePath += "big.png";
        _texture_rect = sf::IntRect({0, 0}, {16, 32});
        _sprite.setOrigin({8, 24});
        _sprite.setTextureRect(_texture_rect);
    }
    else if (_size == 2) {
        filePath += "fire.png";
        _texture_rect = sf::IntRect({0, 0}, {16, 32});
        _sprite.setOrigin({8, 24});
        _sprite.setTextureRect(_texture_rect);
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

void player::_draw(sf::RenderWindow *window, int debug)
{
    (*window).draw(_sprite);
    if (debug == 1) {
        (*window).draw(*_leftHitBox);
        (*window).draw(*_rightHitBox);
        (*window).draw(*_topHitBox);
        (*window).draw(*_bottomHitBox);
    }
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


void player::actualize(game *game)
{
    _onGround = false;
    player::_checkCollision(game->getMap());

    player::_checkInvincibility();
    player::_handleInput();
     
    if (_position.x < int(game->camera->getCenter().x - (game->camera->getSize().x / 2) + (8 * _scale))) {
        _position.x = int(game->camera->getCenter().x - (game->camera->getSize().x / 2) + (8 * _scale));
    }
    _position.y += _velocity.y;
    if (_velocity.x >= (MINIMUM_WALK_VELOCITY * _scale) || _velocity.x <= -(MINIMUM_WALK_VELOCITY * _scale)) {
        _position.x += _velocity.x;
        if (_position.x < int(game->camera->getCenter().x - (game->camera->getSize().x / 2) + (8 * _scale))) {
            _position.x = int(game->camera->getCenter().x - (game->camera->getSize().x / 2) + (8 * _scale));
            _velocity.x = 0;
        }
        if (_position.x > (game->getMap().size() - 0.75) * 16 * _scale) {
            _position.x = (game->getMap().size() - 0.75) * 16 * _scale;
            _velocity.x = 0;
        }
    }
    if (!_facingRight)
        _sprite.setScale({-_scale, _scale});
    else
        _sprite.setScale({_scale, _scale});

    _leftHitBox->setPosition({_position.x - 8 * _scale, _position.y});
    _rightHitBox->setPosition({_position.x + 8 * _scale, _position.y});
    _topHitBox->setPosition({_position.x, _position.y - 8 * _scale});
    _bottomHitBox->setPosition({_position.x, _position.y + 8 * _scale});
    _sprite.setPosition(_position);
    player::_draw(game->_window, game->getDebug());
}

void player::_checkCollision(std::vector<std::vector<block*>> map)
{
    int top_pos = floor((_velocity.y + _position.y - (8 * _scale)) / (16 * _scale));
    int middle_pos = floor((_velocity.y + _position.y) / (16 * _scale));
    int bottom_pos = floor((_velocity.y + _position.y + (8 * _scale)) / (16 * _scale));
    int left_pos = floor((_velocity.x + _position.x - (6 * _scale)) / (16 * _scale));
    int right_pos = floor((_velocity.x + _position.x + (6 * _scale)) / (16 * _scale));

    if (map[left_pos][middle_pos] || map[right_pos][middle_pos])
        _velocity.x = 0;
    if  (map[left_pos][bottom_pos] || map[right_pos][bottom_pos]) {
        // printf("%f\n", _velocity.y);
        _onGround = true;
        _velocity.y = 0;
    }
    if (map[left_pos][top_pos] || map[right_pos][top_pos])
        _velocity.y = 0;
    // if (map[pos_x][pos_y - 1] || map[pos_x + 1][pos_y - 1]) {
    //     _velocity.y = 0;
    //     _onGround = true;
    //     // _position.y = pos_y  * 16 * 4;
    // }
}
