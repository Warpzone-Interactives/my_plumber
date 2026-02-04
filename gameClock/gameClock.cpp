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
    whatReset = 0;
}

void gameClock::clockUpdater()
{
    time = _clock.getElapsedTime();
    seconds = time.asMicroseconds() / 1000000.0;
}

void gameClock::reset()
{
    _clock.restart();
    whatReset = (whatReset + 1) % (resetTime.size() + 1);
    seconds = 0;
}

int gameClock::actionNeed()
{
    clockUpdater();
    if ((seconds) > resetTime[whatReset]) {
        reset();
        return 1;
    }
    return 0;
}
