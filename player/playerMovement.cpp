/*
** EPITECH PROJECT, 2026
** my_plumber
** File description:
** playerMovement
*/

#include "game.hpp"

void player::_handleIdleInput()
{
    if (_skidding == false) {
        if (_velocity.x > (RELEASE_DECELERATION * _scale))
            _velocity.x -= (RELEASE_DECELERATION * _scale);
        if (_velocity.x < -(RELEASE_DECELERATION * _scale))
            _velocity.x += (RELEASE_DECELERATION * _scale);
    }
    else {
        if (_velocity.x > (SKIDDING_DECELERATION * _scale))
            _velocity.x -= (SKIDDING_DECELERATION * _scale);
        if (_velocity.x < -(SKIDDING_DECELERATION * _scale))
            _velocity.x += (SKIDDING_DECELERATION * _scale);
    }
    if (-(RELEASE_DECELERATION * _scale) <= _velocity.x && _velocity.x <= RELEASE_DECELERATION)
        _velocity.x = 0;
}

void player::_updateMovementWalking(int direction)
{
    int addapter = 1;

    if (direction == -1)
        return _handleIdleInput();
    if (direction == 0)
        addapter = -1;
    if (_velocity.x * addapter >= -(SKID_TURNAROUND_SPEED * _scale)) {
        _velocity.x += addapter * (WALKING_ACCELERATION * _scale);
        _skidding = false;
        if (_animClock->actionNeed(0.125) == 1) {
            _choosed_exture = (_choosed_exture % 3) + 1;
            _texture_rect.left = _choosed_exture * 16;
            _sprite.setTextureRect(_texture_rect);
        }
    } else {
        _velocity.x += addapter * (SKIDDING_DECELERATION * _scale);
        _skidding = true;
    }
    if (_velocity.x * addapter > (MAXIMUM_WALK_SPEED * _scale))
        _velocity.x = addapter * (MAXIMUM_WALK_SPEED * _scale);
}

void player::_updateMovementRunning(int direction)
{
    int addapter = 1;

    if (direction == -1) {
        _runningFramesLeft = 0;
        return _handleIdleInput();
    }
    if (direction == 0)
        addapter = -1;
    if (_velocity.x * addapter >= addapter * -addapter * (SKID_TURNAROUND_SPEED * _scale)) {
        _velocity.x += addapter * (RUNNING_ACCELERATION * _scale);
        _skidding = false;
        if (_animClock->actionNeed(0.0635) == 1) {
            _choosed_exture = (_choosed_exture % 3) + 1;
            _texture_rect.left = _choosed_exture * 16;
            _sprite.setTextureRect(_texture_rect);
        }
    } else {
        _velocity.x += addapter * (SKIDDING_DECELERATION * _scale);
        _skidding = true;
        if (_animClock->actionNeed(0.0635) == 1) {
            _choosed_exture = 4;
            _texture_rect.left = _choosed_exture * 16;
            _sprite.setTextureRect(_texture_rect);
        }
    }
    if (_velocity.x * addapter > addapter * addapter * (MAXIMUM_RUNNING_SPEED * _scale))
        _velocity.x = addapter * (MAXIMUM_RUNNING_SPEED * _scale);
} //actuellement mario "snap" à la walk speed directement quand il ne court plus (il ne ralentit pas progressivement).

void player::_handleJumping()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && _onGround) {
        if (_texture_rect.left != 80) {
            _texture_rect.left = 80;
            _sprite.setTextureRect(_texture_rect);
        }
        _animated = 1;
        if (_velocity.x < 1 * _scale)
            _velocity.y += V_L1_UP * _scale;
        if (_velocity.x >= 1 * _scale && _velocity.x < 2.3125 * _scale)
            _velocity.y += V_1T24_UP * _scale;
        if (_velocity.x >= 2.3125 * _scale)
            _velocity.y += V_25M_UP * _scale;
        _onGround = false;
        _jumpStartingVelocity = _velocity.x;
        if (-MAXIMUM_WALK_SPEED * _scale < _velocity.x && _velocity.x < MAXIMUM_WALK_SPEED * _scale)
            _maxAirSpeed = MAXIMUM_WALK_SPEED * _scale;
        else
            _maxAirSpeed = MAXIMUM_RUNNING_SPEED * _scale;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !_onGround) {
        player::_texture_rect.left = 80;
        player::_sprite.setTextureRect(_texture_rect);
        _animated = 1;
        if (_velocity.x < 1 * _scale)
            _velocity.y += V_L1_DWN_A * _scale;
        if (_velocity.x >= 1 * _scale && _velocity.x < 2.3125 * _scale)
            _velocity.y += V_1T24_DWN_A * _scale;
        if (_velocity.x >= 2.3125 * _scale)
            _velocity.y += V_25M_DWN_A * _scale;
    }
    else if (!_onGround) {
        _animated = 1;
        if (_velocity.x < 1 * _scale)
            _velocity.y += V_L1_DWN * _scale;
        if (_velocity.x >= 1 * _scale && _velocity.x < 2.3125 * _scale)
            _velocity.y += V_1T24_DWN * _scale;
        if (_velocity.x >= 2.3125 * _scale)
            _velocity.y += V_25M_DWN * _scale;
    }
    if (_velocity.y > V_MAX * _scale)
        _velocity.y = V_OVERFLOW * _scale;
}

void player::_airPhysics(int direction)
{
    if (direction == 0 && _velocity.x >= 0) {
        if (_velocity.x >= MAXIMUM_WALK_SPEED * _scale)
            _velocity.x -= RUNNING_ACCELERATION * _scale;
        else if (_jumpStartingVelocity > V_SLOW_TRESHOLD * _scale)
            _velocity.x -= RELEASE_DECELERATION * _scale;
        else
            _velocity.x -= WALKING_ACCELERATION * _scale;
    }
    if (direction == 0 && _velocity.x < 0) {
        if (_velocity.x > -MAXIMUM_WALK_SPEED * _scale)
            _velocity.x -= WALKING_ACCELERATION * _scale;
        else
            _velocity.x -= RUNNING_ACCELERATION * _scale;
    }
    if (direction == 1 && _velocity.x >= 0) {
        if (_velocity.x < MAXIMUM_WALK_SPEED * _scale)
            _velocity.x += WALKING_ACCELERATION * _scale;
        else
            _velocity.x += RUNNING_ACCELERATION * _scale;
    }
    if (direction == 1 && _velocity.x < 0) {
        if (_velocity.x >= MAXIMUM_WALK_SPEED * _scale)
            _velocity.x += RUNNING_ACCELERATION * _scale;
        else if (_jumpStartingVelocity > V_SLOW_TRESHOLD * _scale)
            _velocity.x += RELEASE_DECELERATION * _scale;
        else
            _velocity.x += WALKING_ACCELERATION * _scale;
    }
    if (_velocity.x > _maxAirSpeed)
        _velocity.x = _maxAirSpeed;
    if (_velocity.x < -_maxAirSpeed)
        _velocity.x = -_maxAirSpeed;
}

void player::_handleInput()
{
    int direction = -1;

    _animated = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        _runningFramesLeft = 10;
    else if (_runningFramesLeft != 0)
        _runningFramesLeft--;
    if (_character == "mario") {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            direction = 0;
            _animated = 1;
            if (_onGround)
                _facingRight = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            direction = 1;
            _animated = 1;
            if (_onGround)
                _facingRight = true;
        }
    } else {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            direction = 0;
            _animated = 1;
            if (_onGround)
                _facingRight = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            direction = 1;
            _animated = 1;
            if (_onGround)
                _facingRight = true;
        }
    }
    _handleJumping();
    if (_onGround) {
        if (_runningFramesLeft == 0)
            player::_updateMovementWalking(direction);
        else
            player::_updateMovementRunning(direction);
    }
    else
        player::_airPhysics(direction);
    if(_animated == 0) {
        player::_texture_rect.left = 0;
        player::_sprite.setTextureRect(_texture_rect);
    }
}
