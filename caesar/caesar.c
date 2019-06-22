#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int codify(string original, int k);
bool isvalid(int letter);
int last(bool upper);
int first(bool upper);

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        string plaintext = get_string("plaintext:");
        printf("ciphertext:");
        codify(plaintext, atoi(argv[1]));
    }
    else
    {
        printf("Only one argument is allowed");
        return 1;
    }
}

int codify(string original, int k)
{
    for (int i = 0, n = strlen(original); i < n; i++)
    {
        if (isvalid(original[i]))
        {
            bool upper = isupper(original[i]);
            int newstring = original[i] + k;
            int lastletter = last(upper);
            int firstletter = first(upper);
            while (firstletter > newstring || lastletter < newstring)
            {
                int difference = newstring - lastletter - 1;
                newstring = firstletter + difference;
            }
            printf("%c", (char) newstring);
        }
        else
        {
            printf("%c", original[i]);
        }
    }
    printf("\n");
    return 0;
}

bool isvalid(int letter)
{
    if ((letter > 64 && letter < 91) || (letter > 96 && letter < 123))
    {
        return true;
    }
    return false;
}

int last(bool upper)
{
    if (upper)
    {
        return 90;
    }
    return 122;
}

int first(bool upper)
{
    if (upper)
    {
        return 65;
    }
    return 97;
}