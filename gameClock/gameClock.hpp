/*
** EPITECH PROJECT, 2026
** my_plumber
** File description:
** clock
*/

#include "my.hpp"

#ifndef CLOCK_HPP
#define CLOCK_HPP

class gameClock
{
public:
    gameClock(std::vector<double> resetValue);
    ~gameClock() = default;

    void clockUpdater();
    void reset();
    bool actionNeed(double timer_reset);
    
private:
    sf::Clock _clock;
    sf::Time time;
    double seconds;
    int resetId;
    std::vector<double> resetTime;
};

#endif
