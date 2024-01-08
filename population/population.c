#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    // TODO: Prompt for start size
    int min;
    do
    {
        min = get_int("Start size: ");
    }
    while (min < 9);

    // TODO: Prompt for end size
    int max;
    do
    {
        max = get_int("End size: ");
    }
    while (max < min);

    // TODO: Calculate number of years until we reach threshold
    int c = min;
    int y = 0;
    while (c < max)
    {
        c = round(c + (c / 3) - (c / 4));
        y++;
    }
    // TODO: Print number of years
    printf("Years: %i\n", y);
}