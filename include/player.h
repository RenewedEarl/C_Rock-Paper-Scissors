#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>

struct Player
{
    int action;
    bool winner;
};

extern struct Player player_character;

#endif
