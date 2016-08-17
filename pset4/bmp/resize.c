/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }
    int n=atoi(argv[1]);
    if(n>100 || n<1)
    {
        printf(" n should be positive and less than 101\n");
        return 1;
    }
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
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
    
    //saving initial copies of width and height of the image
    int w1=bi.biWidth,h1=bi.biHeight;
    
    //saving the new width and height in place of original image's width and height
    bi.biWidth=n*bi.biWidth;
    bi.biHeight=n*bi.biHeight;

     // determine padding for scanlines
    int padding =  (4 - (w1 * sizeof(RGBTRIPLE)) % 4) % 4,npadding=(4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //printf("bfSize=%d\tbiSizeImage=%d\twidth=%d\theight=%d\tpadding=%d\n",bf.bfSize,bi.biSizeImage,w1,h1,padding);

    //formula for biSizeImage
    bi.biSizeImage=( bi.biWidth*sizeof(RGBTRIPLE) + npadding)* abs(bi.biHeight);
    bf.bfSize=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+bi.biSizeImage;
    //printf("new\nbfSize=%d\tbiSizeImage=%d\twidth=%d\theight=%d\tpadding=%d\n",bf.bfSize,bi.biSizeImage,bi.biWidth,bi.biHeight,npadding);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // temporary storage
    RGBTRIPLE triple;
                
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(h1); i < biHeight; i++)
    {
        for (int l = 0; l < n; l++)
        {
             // skip over padding, if any
            fseek(inptr, sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER) + (w1*sizeof(RGBTRIPLE) + padding)*i, SEEK_SET);

            // iterate over pixels in scanline
            for (int j = 0; j < w1; j++)
            {
                
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
    
                for(int k=0;k<n;k++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // then add padding
            for (int k = 0; k < npadding; k++)
            {
                fputc(0x00, outptr);
            }
        }
    }
    
    //free(triple);
    
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
