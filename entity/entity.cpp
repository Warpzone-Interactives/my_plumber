/*
** EPITECH PROJECT, 2026
** my_plumber
** File description:
** entity
*/

#include "entity.hpp"

void addCoin(game *game, entity *entity)
{
    game->coinCount++;
    printf("coin\n");
    entity->kill();
}

void addLife(game *game, entity *entity)
{
    game->lifeCount++;
    printf("oneup\n");
    entity->kill();
}

void sizeUp(game *game, entity *entity)
{
    //trouver le player le plus proche
    game->_player1->sizeUp();
    printf("up\n");
    entity->kill();
}

void sizeDown(game *game, entity *entity)
{
    //trouver le player le plus proche
    game->_player1->sizeDown();
}

void shellThrow(game *game, entity *entity)
{
    entity->kill();
}

entity::entity(sf::Vector2f position, char m, sf::Texture texture, float scale)
{
    _scale = int(scale);
    _position = position;
    _position.x = (_position.x + 8) *_scale;
    _position.y = (_position.y + 8) *_scale;
    _texture = texture;
    _sprite.setTexture(_texture);
    _what = m;
    _alive = true;
    _runningFramesLeft = 0;
    _animClock = NULL;
    _facingRight = true;
    _leftHitBox = NULL;
    _rightHitBox = NULL;
    _topHitBox = NULL;
    _bottomHitBox = NULL;
    _next = NULL;

    sf::FloatRect rect({position.x, position.y}, {16 * scale, 16 *scale});
    _hitBox = rect;

    _determineCollisionEffect(_what);
    if (_what == 'o' || _what == 'u' || _what == 'i' || _what == 'c')
        _is_object();
}

void entity::_determineCollisionEffect(char what)
{
    switch (what) {
        case 'o':
            _onCollisionEffect = &addLife;
            return;
        case 'u':
            _onCollisionEffect = &sizeUp;
            return;
        case 'i':
            _onCollisionEffect = &sizeUp;
            return;
        case 'c':
            _onCollisionEffect = &addCoin;
            return;
        case 'k':
            _onCollisionEffect = &shellThrow;
            return;
        case 'K':
            _onCollisionEffect = &sizeDown;
            return;
        case 'g':
            _onCollisionEffect = &sizeDown;
            return;
        default:
            _onCollisionEffect = NULL;
            return;
    }
}

void entity::_is_object()
{
    _animated = 0;
    _texture_rect = sf::IntRect({0, 0}, {16, 16});
    _sprite = sf::Sprite(_texture);
    _sprite.setTextureRect(_texture_rect);
    _sprite.setPosition(_position);
    _sprite.setScale({_scale, _scale});
    _sprite.setOrigin({8, 8});
    if (_what == 'i') {
        _nbAnime = 4;
        _animClock = new gameClock({0.015625});
    } else
        _nbAnime = 1;
}

void entity::append(entity *n_entity)
{
    if (_next == NULL)
        _next = n_entity;
    else
        _next->append(n_entity);
}

void entity::actualize(game *game)
{
    if (!_alive)
        return;
    _draw(*(game->_window));
    isColliding(game);
    if (_animClock != NULL && _animClock->actionNeed(0.03125) == 1)
        _anime();
    if (_next != NULL)
        _next->actualize(game);
}

void entity::_draw(sf::RenderWindow &window)
{
    window.draw(_sprite);
}

void entity::_anime()
{
    if (_nbAnime > 1) {
        _texture_rect.left = (_texture_rect.left + 16) % (_nbAnime * 16);
        _sprite.setTextureRect(_texture_rect);
    }
}

void entity::isColliding(game *game)
{
    if (_hitBox.intersects(game->_player1->hitbox))
        _onCollisionEffect(game, this); //this c'est l'objet entité
}

void entity::kill()
{
    _alive = false;
}
