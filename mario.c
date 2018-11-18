#include <stdio.h>
#include <cs50.h>

int repeat(char c, int n);

int main(void)
{
    int pyramidHeight = 0;
    do
    {
        pyramidHeight = get_int("Half-pyramid height: ");
    }
    while (0 > pyramidHeight || pyramidHeight > 23);
    int top = 2;
    int base = pyramidHeight + 1;
    int line = top;
    for (int i = pyramidHeight; i > 0; i--)
    {
        repeat(' ', base - line);
        repeat('#', line);
        printf("\n");
        line++;
    }
}

int repeat(char c, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%c", c);
    }
    return 1;
}