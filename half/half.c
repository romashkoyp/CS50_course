// Calculate your half of a restaurant bill
// Data types, operations, type casting, return value

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    float bill_amount = get_float("Bill before tax and tip: ");
    float tax_percent = get_float("Sale Tax Percent: ");
    int tip_percent = get_int("Tip percent: ");
    int b = get_int("How many people: ");
    float tax = bill_amount * tax_percent / 100;
    float tip = (bill_amount + tax) * tip_percent / 100;
    float a = (bill_amount + tax + tip) / b;

printf("You will owe $%.2f each!\n", a);
}