#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    // TODO: Prompt for start size
    int min = 5569431;

    // TODO: Prompt for end size
    int max;
    max = get_int("End size: ");

    // TODO: Calculate number of years until we reach threshold
    int current = min;
    int years = 2023;
    while (current > max)
    {
        current = current - 8353;
        years++;
    }
    // TODO: Print number of years
    printf("Years: %i\n", years);
}