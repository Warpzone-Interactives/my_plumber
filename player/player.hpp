/*
** EPITECH PROJECT, 2025
** my_plumber
** File description:
** my.hpp
*/

#include "my.hpp"

//btw le facingRight et pas facing_right c'est camel case contrairement à snake case (en C)
//jsp si c'est mieux mais alecsandra l'a fait comme ça donc bon

class player
{
public:
    player(int size, sf::Vector2f position, char m);
    ~player() = default;

    void sizeUp();
    void sizeDown();
    void giveStar();
    void shoot();

    void draw(sf::RenderWindow &window);

private:
    std::string character; // mario ou luigi

    int _size;              // 0: small, 1: big, 2: fire
    bool _alive;            // true: vivant, false: mort
    bool _invincible;       // pour après avoir pris des dégats, true pendant une durée
    sf::Clock _invincibilityClock; //durée d'invincibilité, quand > à Duration alors _invincible = false
                                   //et on destroy la clock ?
    float _invincibilityDuration;  //temps d'invincibilité en secondes (donc différent si étoile ou dégats)

    sf::Vector2f _position; // Position (mais nan jure)
    sf::Vector2f _velocity; // Vitesse
    bool _onGround; //Pour check si il peut sauter
    bool _facingRight; // true: droite, false: gauche

    sf::Sprite _sprite; //sprite
    sf::Texture _texture; //texture

    void _kill();
    void _chooseTexture();
    void _setTexture(std::string filePath);

    //Il reste bcp de méthodes à mettre et surement deux trois variables mais il est tard :(
};
