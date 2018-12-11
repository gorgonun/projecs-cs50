#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: file to recover\n");
        return 1;
    }

    // remember file name
    char *infile = argv[1];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open the file\n");
        return 2;
    }

    // // temporary storage
    // unsigned char checker[2];

    // // jump over 0x00
    // while (!feof(inptr))
    // {
    //     fread(&checker, 1, 2, inptr);
    //     if (checker[0] == 0xff &&
    //         checker[1] == 0xd8)
    //     {
    //         fseek(inptr, -2, SEEK_CUR);
    //         break;
    //     }
    //     else
    //     {
    //         fseek(inptr, -1, SEEK_CUR);
    //     }
    // }

    unsigned char buffer[513];

    // counter of images
    int counter = 0;
    FILE *outptr;
    int *first = (int *) malloc(sizeof(int));

    while (fread(&buffer, 1, 512, inptr) == 512)
    {
        // check header
        if (buffer[0] == 0xff &&
           buffer[1] == 0xd8 &&
           buffer[2] == 0xff &&
           (buffer[3] & 0xf0) == 0xe0)
           {
                if (counter != 0 || *first == 1)
                {
                    counter++;
                    fclose(outptr);
                }
                if (counter == 0)
                {
                    *first = 1;
                }
                char filename[8];
                sprintf(filename, "%03i.jpg", counter);

                // open output file
                outptr = fopen(filename, "w");
                fwrite(&buffer, 1, 512, outptr);
           }
        else if (*first == 1)
        {
            fwrite(&buffer, 1, 512, outptr);
        }
        else
        {
            fseek(inptr, -511, SEEK_CUR);
        }
    }
    fclose(outptr);
    fclose(inptr);
}