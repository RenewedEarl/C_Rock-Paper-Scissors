#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <stdio.h>

static int playerActionInput(char *prompt, char *buffer, size_t size);
int generateOpponentAction(int min, int max);
void game();

#endif
