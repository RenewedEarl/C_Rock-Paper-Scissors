#include <time.h>
#include <stdlib.h>

#include "gameplay.h"

int main()
{
    srand((unsigned int)time(NULL));

    game();

    return 0;
}
