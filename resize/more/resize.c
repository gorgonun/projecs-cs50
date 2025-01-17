// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize size infile outfile\n");
        return 1;
    }
    if (*argv[1] > 100 || *argv[1] < 0)
    {
        fprintf(stderr, "Size must be >= 100");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // remember size
    float n = atof(argv[1]);

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    int oldbiWidth = bi.biWidth;
    int oldbiHeight = bi.biHeight;

    // change width and heigth by size
    bi.biWidth *= n;
    bi.biHeight *= n;

    int newPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // update size and sizeImage
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + newPadding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding = (4 - (oldbiWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(oldbiHeight); i < biHeight; i++)
    {
        if (abs(oldbiHeight) > abs(bi.biHeight))
        {
            if (i >= abs(bi.biHeight))
            {
                break;
            }
        }
        // temporary count for n < 1
        float countN = bi.biWidth;
        RGBTRIPLE tempArray[bi.biWidth];
        int counter = 0;

        // iterate over pixels in scanline
        for (int j = 0; j < oldbiWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            if (countN >= 1)
            {
                for (int k = 0; k < n; k++)
                {
                    // write RGB triple to outfile n times
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    tempArray[counter] = triple;
                    counter ++;
                    countN -= 1;
                }
            }
        }
        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
        // then add it back (to demonstrate how)

        for (int k = 0; k < newPadding; k++)
        {
            fputc(0x00, outptr);
        }

        // repeat writing to horizontal resizing
        for (int o = 0; o < (int) n - 1; o++)
        {
            for (int m = 0; m < bi.biWidth; m ++)
            {
                fwrite(&tempArray[m], sizeof(RGBTRIPLE), 1, outptr);
            }

            for (int k = 0; k < newPadding; k++)
            {
                fputc(0x00, outptr);
            }
        }
 }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
