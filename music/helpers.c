// Helper functions for music

#include <cs50.h>
#include <math.h>
#include <string.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int numerator = fraction[0] - 48;
    int denominator = fraction[2] - 48;
    while (denominator != 8)
    {
        numerator *= 2;
        denominator *= 2;
    }
    return numerator;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    char listNotes[] = {'C', 'D', 'E', 'F', 'G', 'A', 'B'};
    double listValues[] = {-9.0, -7.0, -5.0, -4.0, -2.0, 0.0, 2.0};
    char letter = note[0];
    int octave = note[1] - 48;
    int fix = 0;
    double nominator = 0.0;
    int calculum;
    for (int i = 0; i < 7; i++)
    {
        if (listNotes[i] == letter)
        {
            nominator = listValues[i];
            break;
        }
    }
    if (strlen(note) == 3)
    {
        char charfix = note[1];
        if (charfix == '#')
        {
            fix = 1;
        }
        else
        {
            fix = -1;
        }
        octave = note[2] - 48;
    }
    int difference = abs(octave - 4);
    if (octave >= 4)
    {
        nominator += fix + 12 * difference;
    }
    else
    {
        nominator += fix - 12 * difference;
    }
    double denominator = nominator / 12.0;
    calculum = round(440 * pow(2.0, denominator));
    return calculum;

}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (strlen(s) == 0)
    {
        return true;
    }
    return false;
// TODO
}
