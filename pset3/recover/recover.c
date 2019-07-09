#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdint.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover rawFileName\n");
        return 1;
    }
    char *infile = argv[1];
    char filename[20];
    int counter = 0;
    
    FILE *rawfile = fopen(infile, "r");
    FILE *readyFile;
	bool started = false;
    //just because x 512
    uint8_t block[512];
    //drop, if no such file exist
    if (rawfile == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }
    
    while(fread(&block, 1, 512, rawfile) == 512){
        if(block[0]==0xff &&
            block[1]==0xd8 &&
            block[2]==0xff &&
            (block[3] & 0xf0) == 0xe0
            ){
                //close previously opened file, if there was any
                if(started){
                    fclose(readyFile);
                }
                //dynamicaly generate namee
                sprintf(filename, "%03d.jpg", counter);
                readyFile = fopen(filename, "w");
                
                fwrite(&block, 1, 512, readyFile); 
                //indicate that file started
                started = true;
                //keep track for filenames
                counter++;
        }
        else if(started){
            //write this block into started file
            fwrite(&block, 1, 512, readyFile);
        }
    }

    // close rawfile
    fclose(rawfile);
    // close readyFile
    fclose(readyFile);
}