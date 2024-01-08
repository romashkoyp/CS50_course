#include <stdio.h>
#include <cs50.h>

//Hello world
int main(void)
{
    string name = get_string("What's your name? ");
    printf("Hello, %s!\n", name);
}