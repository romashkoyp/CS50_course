#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
// Get string
    string text = get_string("Message: ");

// Decompose the text into individual characters

    for (int i = 0; i < strlen(text); i++)
    {
        char c = text[i];
// Replace characters with ASCII decimal code
        int ascii = (int) c;
        /*printf("decimel %i\n", ascii);*/

// Convert each character code to binary
        int b1 = ascii % 2;
        int b2 = (ascii / 2) % 2;
        int b3 = ((ascii / 2) / 2) % 2;
        int b4 = (((ascii / 2) / 2) / 2) % 2;
        int b5 = ((((ascii / 2) / 2) / 2) / 2) % 2;
        int b6 = (((((ascii / 2) / 2) / 2) / 2) / 2) % 2;
        int b7 = ((((((ascii / 2) / 2) / 2) / 2) / 2) / 2) % 2;
        int b8 = (((((((ascii / 2) / 2) / 2) / 2) / 2) / 2) / 2) % 2;
        /*printf("%i%i%i%i%i%i%i%i\n", b8, b7, b6, b5, b4, b3, b2, b1);*/

// Send each binary code to a print-function
        print_bulb(b8);
        print_bulb(b7);
        print_bulb(b6);
        print_bulb(b5);
        print_bulb(b4);
        print_bulb(b3);
        print_bulb(b2);
        print_bulb(b1);
        print_bulb(2);
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
    else if (bit == 2)
    {
        // New row
        printf("\n");
    }
}