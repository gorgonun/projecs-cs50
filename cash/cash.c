#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float change = 0;
    do
    {
        change = get_float("Change owed: ");
    }
    while (0 >= change);
    int cents = lround(change * 100);
    int numberOfCoins = 0;
    while (cents >= 25)
    {
        cents -= 25;
        numberOfCoins++;
    }
    while (cents >= 10)
    {
        cents -= 10;
        numberOfCoins++;
    }
    while (cents >= 5)
    {
        cents -= 5;
        numberOfCoins++;
    }
    while (cents >= 1)
    {
        cents -= 1;
        numberOfCoins++;
    }
    printf("%i\n", numberOfCoins);
}