#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int cypher(char k);
bool isvalid(string text);
int codify(string original, string list);
int last(bool upper);
int first(bool upper);
int circularlist(string list, int position);

int main(int argc, string argv[])
{
    if (argc == 2 && isvalid(argv[1]))
    {
        string plaintext = get_string("plaintext:");
        printf("ciphertext:");
        codify(plaintext, argv[1]);
    }
    else
    {
        printf("Invalid argument");
        return 1;
    }
}

int codify(string original, string list)
{
    for (int i = 0, l = 0, n = strlen(original); i < n; i++)
    {
        if (isalpha(original[i]))
        {
            int k = cypher(circularlist(list, l));
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
            l++;
        }
        else
        {
            printf("%c", original[i]);
        }
    }
    printf("\n");
    return 0;
}

bool isvalid(string text)
{
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]) == false)
        {
            return false;
        }
    }
    return true;
}

int cypher(char k)
{
    k = (int) toupper(k) - first(true);
    return k;
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

int circularlist(string list, int position)
{
    int size = strlen(list);
    while (position >= size)
    {
        position -= size;
    }
    return list[position];
}