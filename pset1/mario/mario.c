#include <stdio.h>
#include <cs50.h>

void typursion (int height, int iniHeight);
void printer (int times, char charToPrint);

int main(void){
    int iniHeight;
    do{
        iniHeight = get_int("Height:");
    }
    while( iniHeight<1||iniHeight>8 );
    typursion(iniHeight, iniHeight);
}

void typursion (int height, int iniHeight){
    if (height != 0){
        printer (height-1,' ');             // -1 indicate length of string minus #
    	printer (iniHeight -height +1,'#'); // should be at least one #
    	printer (2,' ');
    	printer (iniHeight -height +1,'#');
    	printf("\n");
        height--;
        typursion(height, iniHeight);
    }
}

void printer (int times,char charToPrint )
{
	for (int i = 0; i<times; i++)
	{
		printf("%c", charToPrint);
	}
}
