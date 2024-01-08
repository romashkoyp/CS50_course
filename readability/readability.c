#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    //Get text from a user
    string text = get_string("Text: ");
    /*printf("%s\n", text);*/

    //Calculate letters
    int letters = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        if (isupper(text[i]))
        {
            letters++;
        }
        else if (islower(text[i]))
        {
            letters++;
        }
    }
    /*printf("%i letters\n", letters);*/

    //Calculate words
    int words = 1;

    for (int j = 0; j < strlen(text); j++)
    {
        if (isspace(text[j]))
        {
            words++;
        }
    }
    /*printf("%i words\n", words);*/

    //Calculate sentences
    int sentences = 0;

    for (int k = 0; k < strlen(text); k++)
    {
        if (text[k] == '.' || text[k] == '!' || text[k] == '?')
        {
            sentences++;
        }
    }
    /*printf("%i sentences\n", sentences);*/

    //Calculate index
    float index = (0.0588 * (((float) letters / words) * 100) - 0.296 * (((float) sentences / words) * 100) - 15.8);
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    if (index > 16)
    {
        printf("Grade 16+\n");
    }
    if (index > 1 && index < 16)
    {
        printf("Grade %i\n", (int) round(index));
    }
}