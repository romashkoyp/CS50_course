#include <cs50.h>
#include <stdio.h>

int main(void)
{
//Get positive number
    long number;
    do
    {
        number = get_long("Number: ");
    }
    while (number < 0);

//Calculate checksum
    int a = ((number % 100) / 10 * 2);
    int b = ((number % 10000) / 1000 * 2);
    int c = ((number % 1000000) / 100000 * 2);
    int d = ((number % 100000000) / 10000000 * 2);
    int e = ((number % 10000000000) / 1000000000 * 2);
    int f = ((number % 1000000000000) / 100000000000 * 2);
    int g = ((number % 100000000000000) / 10000000000000 * 2);
    int h = ((number % 10000000000000000) / 1000000000000000 * 2);

    int a1 = (a % 100) / 10 + (a % 10);
    int b1 = (b % 100) / 10 + (b % 10);
    int c1 = (c % 100) / 10 + (c % 10);
    int d1 = (d % 100) / 10 + (d % 10);
    int e1 = (e % 100) / 10 + (e % 10);
    int f1 = (f % 100) / 10 + (f % 10);
    int g1 = (g % 100) / 10 + (g % 10);
    int h1 = (h % 100) / 10 + (h % 10);
    int sum1 = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1;

    int a2 = (number % 10);
    int b2 = ((number % 1000) / 100);
    int c2 = ((number % 100000) / 10000);
    int d2 = ((number % 10000000) / 1000000);
    int e2 = ((number % 1000000000) / 100000000);
    int f2 = ((number % 100000000000) / 10000000000);
    int g2 = ((number % 10000000000000) / 1000000000000);
    int h2 = ((number % 1000000000000000) / 100000000000000);
    int sum2 = a2 + b2 + c2 + d2 + e2 + f2 + g2 + h2;
    int sum3 = sum2 + sum1;

//Check VALID or INVALID card
    string inv = "INVALID";
    if ((sum3 % 10) != 0)
    {
        printf("%s\n", inv);
        return 0;
    }

//Check for card length
    int digits = 0;
    while (number > 0)
    {
        number = number / 10;
        digits++;
    }

//Check VISA
    string visa = "VISA";
    if (digits == 16 && h / 2 == 4)
    {
        printf("%s\n", visa);
        return 0;
    }
    else if (digits == 15 && h2 == 4)
    {
        printf("%s\n", visa);
        return 0;
    }
    else if (digits == 14 && g / 2 == 4)
    {
        printf("%s\n", visa);
        return 0;
    }
    else if (digits == 13 && g2 == 4)
    {
        printf("%s\n", visa);
        return 0;
    }

//Check American Express
    string american = "AMEX";
    if (digits == 15 && h2 == 3 && (((g / 2) == 4) || ((g / 2) == 7)))
    {
        printf("%s\n", american);
        return 0;
    }

//Check Master Card
    string master = "MASTERCARD";
    if (digits == 16 && ((h / 2) == 5) && (h2 == 1 || h2 == 2 || h2 == 3 || h2 == 4 || h2 == 5))
    {
        printf("%s\n", master);
        return 0;
    }
    else
    {
        printf("%s\n", inv);
        return 0;
    }
}