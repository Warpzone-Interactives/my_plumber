/*
** EPITECH PROJECT, 2026
** my_plumber
** File description:
** entity
*/

#include "my.hpp"

#ifndef ENTITY_HPP_
    #define ENTITY_HPP_

class game;

class entity
{
public:
    entity(sf::Vector2f position, char m, sf::Texture texture, float scale);
    ~entity() = default;

    void colision(); // prend peut etre player

    void setScale(int scale);

    void kill();

    sf::Vector2f getPos();

    void actualize(game *game);
    void append(entity *n_entity);

    void isColliding(game *game);

private:

    void _is_object();
    void _anime();
    void _draw(sf::RenderWindow &window);
    void _determineCollisionEffect(char what);

    char _what;  // coin, goomba, koopa, shroom etc

    bool _alive;            // true: vivant, false: mort(detruire pour plus le charger)


    sf::Vector2f _position; // Position (mais nan jure) (MDR)
    bool _facingRight; // true: droite, false: gauche

    int _nbAnime;

    sf::RectangleShape *_leftHitBox; // rect for hitbox
    sf::RectangleShape *_rightHitBox; // rect for hitbox
    sf::RectangleShape *_topHitBox; // rect for hitbox
    sf::RectangleShape *_bottomHitBox; // rect for hitbox
    sf::FloatRect _hitBox; // rect for hitbox

    float _scale; //scale of the map
    sf::IntRect _texture_rect; // rect for texture
    sf::Sprite _sprite; //sprite
    sf::Texture _texture; //texture
    gameClock *_animClock;
    int _choosed_exture;
    int _animated;

    int _runningFramesLeft;

    entity *_next;

    void (*_onCollisionEffect)(game *game, entity *self);

    void _chooseTexture();
    void _setTexture(std::string filePath);

    void _handleIdleInput();
    void _updateMovementWalking();
    void _checkCollision(std::vector<std::vector<block*>> map);

};

#endif /* !ENTITY_HPP_ */
