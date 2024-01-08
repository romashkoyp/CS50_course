#include <cs50.h>
#include <stdio.h>

int main(void)
{
//Get positive number from 1 to 8
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

//Build left pyramid
    /*for (int i = 0; i < height; i++)
    {
      for (int j = -1; j < i; j++)
        {
            printf("#");
        }
        printf("\n");
    }*/

//Build right pyramid with dots
    /*for (int line = 0; line < height; line++)
    {
        for (int dots = 0; dots < height - line - 1; dots++)
        {
            printf(" ");
        }
        for (int hash = 0; hash <= line; hash++)
        {
            printf("#");
        }
        printf("\n");
    }*/

//Build difficult Mario pyramid
    for (int line = 0; line < height; line++)
    {
        for (int dots = 0; dots < height - line - 1; dots++)
        {
            printf(" ");
        }
        for (int hash = 0; hash <= line; hash++)
        {
            printf("#");
        }
        printf("  ");
        for (int hash2 = 0; hash2 <= line; hash2++)
        {
            printf("#");
        }
        printf("\n");
    }
}