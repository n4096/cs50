// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }
    //scale
    float f = atof(argv[1]);
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

    // determine padding for scanlines

    
    //TODO modidy bf and bi here
    int oldW = abs(bi.biWidth);
    int oldH = abs(bi.biHeight);
    int oldPad = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bi.biWidth *=f;
    bi.biHeight *=f;
    // bi.biHeight = abs(bi.biHeight);
    int newW = bi.biWidth;
    int newH =bi.biHeight;
    printf("%i,%i\n", newW, newH);
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    //REDO
    bi.biSizeImage = ( bi.biWidth*sizeof(RGBTRIPLE) + padding ) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    
    float counterW = 0;
    float counterH = 0;
    printf("pad%i,old%i\n", padding, oldPad);
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);



    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(oldH); i < biHeight; i++)
    {
        //requiered for vertical repeats count
        for(counterH = counterH + f; counterH>=1; counterH--){
            if(counterW==0){
                fseek(inptr, -bi.biWidth-oldPad, SEEK_CUR);
            }
            
            
            // iterate over pixels in scanline and resize them
            for (int j = 0; j < oldW; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
                
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                for(counterW=counterW +f; counterW>=1; counterW--){
                // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
                counterW = counterW +f -1;
            }
            
            // skip over padding, if any
            fseek(inptr, oldPad, SEEK_CUR);
            // then add it back (to demonstrate how)
            for (int k = 0; k < padding; k++)
            {
                fputc(0x00, outptr);
            }

            

            counterW = 0;
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
