#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    // Recursion limitation
    int n = strlen(input);

    // Case when recursion should stop
    if (n == 1)
    {
        return input[0] - '0';
    }

    // Recursion case
    else
    {
        int number = input[n - 1] - '0'; // Change last symbol to a number from the end
        input[n - 1] = '\0'; // Truncare number from the end for 1 figure
        return number + convert(input) * 10; // Last figure + truncated number
    }
}