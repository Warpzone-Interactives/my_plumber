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
    int actionNeed();
    
private:
    sf::Clock _clock;
    sf::Time time;
    double seconds;
    int whatReset;
    std::vector<double> resetTime;
};

#endif
