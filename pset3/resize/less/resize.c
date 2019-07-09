// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: scale copy infile outfile\n");
        return 1;
    }
    //scale factor
    float scale = atof(argv[1]);
    if (scale<1||scale>100){
        fprintf(stderr, "Scale should be >0 and <=100\n");
        return 1;
    }
    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

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

    //set original and modified resolution
    int originalW = bi.biWidth;
    int originalH = bi.biHeight;
    int newH = floor(scale)*originalH;
    int newW = floor(scale*originalW);
    bi.biWidth = newW;
    bi.biHeight = newH;
    // determine padding for scanlines
    int padding = (4 - (newW * sizeof(RGBTRIPLE)) % 4) % 4;
    int originalP = (4 - (originalW * sizeof(RGBTRIPLE)) % 4) % 4;
    bi.biSizeImage = ( bi.biWidth*sizeof(RGBTRIPLE) + padding ) * abs(newH);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);


    //temp scanline copy
    RGBTRIPLE lineArray[newW];
    //remember positioin of each px for temp scanline
    int counterForLine =0;
    // temporary storage
    RGBTRIPLE triple;
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);


    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(originalH); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < originalW; j++)
        {
            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            for(int k=0; k<scale;k++){
                // write RGB triple to outfile
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                //create scanline copy over iterations
                lineArray[counterForLine] = triple;
                counterForLine++;
            }
            
        }
        // skip over padding, if any
        fseek(inptr, originalP, SEEK_CUR);
        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
        //reset temp array for scanline
        counterForLine =0;
        //copy scanline from temp and add padding
        for(int u =1;u<scale;u++){
            for(int l=0;l<newW;l++){
                triple = lineArray[l];
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);

            }
            for (int k = 0; k < padding; k++)
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
