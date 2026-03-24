/*
** EPITECH PROJECT, 2025
** my_plumber
** File description:
** my.hpp
*/

#include "my.hpp"

#ifndef PLAYER_HPP
#define PLAYER_HPP

class player
{
public:
    player(int size, sf::Vector2f position, char m);
    ~player() = default;

    void sizeUp();
    void sizeDown();
    void giveStar();
    void shoot();

    void setScale(int scale);

    sf::Vector2f getPos();
    sf::Vector2f getVel();
    std::string getChar();
    std::string getSize();
    std::string getFacing();
    std::string getOnGround();
    std::string getAlive();

void actualize(sf::RenderWindow &window, sf::View *camera, std::vector<std::vector<block*>> map);

private:
    std::string _character; // mario ou luigi

    int _size;              // 0: small, 1: big, 2: fire
    bool _alive;            // true: vivant, false: mort
    bool _invincible;       // pour après avoir pris des dégats, true pendant une durée
    sf::Clock _invincibilityClock; //durée d'invincibilité, quand > à Duration alors _invincible = false
                                   //et on destroy la clock ?
    float _invincibilityDuration;  //temps d'invincibilité en secondes (donc différent si étoile ou dégats)

    float _scale; //scale of the map

    sf::Vector2f _position; // Position (mais nan jure) (MDR)
    sf::Vector2f _velocity; // Vitesse
    bool _onGround; //Pour check si il peut sauter
    bool _facingRight; // true: droite, false: gauche

    int _sprite_nb;

    sf::IntRect _texture_rect; // rect for texture
    sf::Sprite _sprite; //sprite
    sf::Texture _texture; //texture
    gameClock *_animClock;
    int _choosed_exture;
    int _animated;

    int _runningFramesLeft;
    bool _skidding;
    float _maxAirSpeed;
    float _jumpStartingVelocity;

    void _draw(sf::RenderWindow &window);
    void _kill();
    void _chooseTexture();
    void _setTexture(std::string filePath);
    void _handleInput();
    void _checkInvincibility();

    //Movement :
    void _handleIdleInput();
    void _updateMovementWalking(int direction);
    void _updateMovementRunning(int direction);
    void _handleJumping();
    void _airPhysics(int direction);
    void _checkCollision(std::vector<std::vector<block*>> map);
    // bool _isOnGround(std::vector<std::vector<block*>>);

    //Il reste bcp de méthodes à mettre et surement deux trois variables mais il est tard :(
};

#endif /* PLAYER_HPP */
