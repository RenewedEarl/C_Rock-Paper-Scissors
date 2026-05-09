#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "actions.h"
#include "player.h"
#include "opponent.h"

#define OK          0
#define NO_INPUT    1
#define TOO_LONG    2

static int playerActionInput(char *prompt, char *buffer, size_t size)
{
    int ch, extra;

    // Get line with buffer overrun protection
    if (prompt != NULL)
    {
        printf("%s", prompt);
        fflush(stdout);
    }
    if (fgets(buffer, size, stdin) == NULL)
        return NO_INPUT;
    
    // If it's too long, there'll be no newline. In that case, flush
    // to the end of line so excess doesn't affect another call
    if (buffer[strlen(buffer) - 1] != '\n')
    {
        extra = 0;
        while (((ch = getchar()) != '\n') && (ch != EOF))
            extra = 1;
        return (extra == 1) ? TOO_LONG : OK;
    }

    // Otherwise remove newline and give string back to the caller
    buffer[strlen(buffer) - 1] = '\0';
    return OK;
}

int generateOpponentAction(int min, int max)
{
    // Taking current time as seed
    unsigned int seed = time(0);
    // Generate the action
    int opponentActionNumber = rand_r(&seed) % (max - min + 1) + min;

    return opponentActionNumber;
}

void game()
{
    int returnCode;
    char answer[16];
    int opponentAction = generateOpponentAction(1, 3);

    printf("Rock, Paper, Scissors!!!\n");

    returnCode = playerActionInput(
        "What would you like to use (Rock, Paper, or Scissors?): ",
        answer,
        sizeof(answer));

    if (strcmp(answer, "Rock") == 0)
        player_character.action = rock_action.id;
    else if (strcmp(answer, "Paper") == 0)
        player_character.action = paper_action.id;
    else if (strcmp(answer, "Scissors") == 0)
        player_character.action = scissors_action.id;
    else
        printf("Invalid Input!\n");

    switch (opponentAction)
    {
        case 1:
            opponent_character.action = rock_action.id;
            break;
        case 2:
            opponent_character.action = paper_action.id;
            break;
        case 3:
            opponent_character.action = scissors_action.id;
            break;
    }
    
    if (player_character.action == 1 && opponent_character.action == 2)
    {
        printf("You have Rock and your opponent has Paper...\n");
        player_character.winner == false;
    }
    else if (player_character.action == 1 && opponent_character.action == 3)
    {
        printf("You have Rock and your opponent has Scissors...\n");
        player_character.winner = true;
    }
    else if (player_character.action == 2 && opponent_character.action == 1)
    {
        printf("You have Paper and your opponent has Rock...\n");
        player_character.winner = true;
    }
    else if (player_character.action == 2 && opponent_character.action == 3)
    {
        printf("You have Paper and your opponent has Scissors...\n");
        player_character.winner = false;
    }
    else if (player_character.action == 3 && opponent_character.action == 1)
    {
        printf("You have Scissors and your opponent has Rock...\n");
        player_character.winner = false;
    }
    else if (player_character.action == 3 && opponent_character.action == 2)
    {
        printf("You have Scissors and your opponent has Paper...\n");
        player_character.winner = true;
    }
    else
    {
        player_character.winner = false;

        if (player_character.action == 1)
        {
            printf("You and your opponent have Rock, so you tie!\n");
            return;
        }
        else if (player_character.action == 2)
        {
            printf("You and your opponent have Paper, so you tie!\n");
            return;
        }
        else
        {
            printf("You and your opponent have Scissors, so you tie!\n");
            return;
        }
    }

    if (player_character.winner == true)
        printf("You win!\n");
    else
        printf("You lose!\n");
}
