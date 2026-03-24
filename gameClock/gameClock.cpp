/*
** EPITECH PROJECT, 2025
** my_plumber
** File description:
** clock
*/

#include "gameClock.hpp"

gameClock::gameClock(std::vector<double> resetValue)
{
    seconds = 0;
    resetTime = resetValue;
    resetId = 0;
}

void gameClock::clockUpdater()
{
    time = _clock.getElapsedTime();
    seconds = time.asMicroseconds() / 1000000.0;
}

void gameClock::reset()
{
    _clock.restart();
    resetId = (resetId + 1) % (resetTime.size());
    seconds = 0;
}

int gameClock::actionNeed(double timer_reset)
{
    if (timer_reset <= 0)
        timer_reset = resetTime[resetId];
    clockUpdater();
    if ((seconds) > timer_reset) {
        reset();
        return 1;
    }
    return 0;
}
