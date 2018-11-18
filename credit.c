#include <cs50.h>
#include <stdio.h>
#include <math.h>

long total_exp(long number);
int owner(long size, long number);
int sum(int owner, long size, long number);

int main(void)
{
    long number = 0;
    do
    {
        number = get_long_long("Credit card number: ");
    }
    while (0 > number);
    long size = total_exp(number);
    if (size == 0)
    {
        printf("INVALID\n");
        return 0;
    }
    int cardOwner = owner(size, number);
    if (cardOwner == 0)
    {
        printf("INVALID\n");
        return 0;
    }
    int result = sum(cardOwner, size, number);
    if (result != 0)
    {
        printf("INVALID\n");
        return 0;
    }
    if (cardOwner == 1)
    {
        printf("VISA\n");
    }
    else if (cardOwner == 2)
    {
        printf("AMEX\n");
    }
    else if (cardOwner == 3)
    {
        printf("MASTERCARD\n");
    }

}

long total_exp(long number)
{
    if (number > 1E13 || number < 56E15)
    {
        if (number / 1E13 > 0 && number / 1E13 < 1)
        {
            return 1E13;
        }
        else if (number / 1E15 > 0 && number / 1E15 < 1)
        {
            return 1E15;
        }
        else if (number / 1E16 > 0 && number / 1E16 < 1)
        {
            return 1E16;
        }
        else
        {
            return 0;
        }
    }
    return 0;

}

int owner(long size, long number)
{
    if (size == 1E13)
    {
        if (number / 1E12 >= 4 && number / 1E12 < 5)
        {
            return 1;
        }
        return 0;
    }
    else if (size == 1E15)
    {
        if ((number / 1E13 >= 34 && number / 1E13 < 35) || (number / 1E13 >= 37 && number / 1E13 < 38))
        {
            return 2;
        }
        return 0;
    }
    else if (size == 1E16)
    {
        if (number / 1E15 >= 4 && number / 1E15 < 5)
        {
            return 1;
        }
        else if (number / 1E14 >= 50 && number / 1E14 < 56)
        {
            return 3;
        }
        return 0;
    }
    return 0;

}

int sum(int owner, long size, long number)
{
    int sum1 = 0;
    int sum2 = 0;
    int totalOwner = 0;
    if (size == 1E13)
    {
        totalOwner = 6;
    }
    else if (size == 1E15)
    {
        totalOwner = 7;
    }
    else if (size == 1E16)
    {
        totalOwner = 8;
    }
    for (int i = totalOwner * 2 ; i > 0; i -= 2)
    {
        long multiplicator = pow(10, i - 1);
        int result = floor(((number / multiplicator) % 10) * 2);
        if (result > 9)
        {
            result = floor(result % 10) + floor(result / 10);
        }
        sum1 += result;
        sum2 += floor((number / (multiplicator / 10)) % 10);
    }
    if (totalOwner % 2 == 1)
    {
        sum2 += floor((number / (size / 10)) % 10);
    }
    return (sum1 + sum2) % 10;
}