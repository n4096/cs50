#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <cs50.h>
#include <string.h>

const char dict[52] = {'A','B','C',
                    'D','E','F','G','H','I','J','K','L','M','N','O','P','Q',
                    'R','S','T','U','V','W','X','Y','Z','a','b','c','d','e',
                    'f','g','h','i','j','k','l','m','n',
                    'o','p','q','s','t','u','v','w','x','y','z'};
char bruted [6] = {'\0','\0','\0','\0','\0','\0'};
char *hash;

int cracker(char *input, char *salt, int k, int pasLenHere);

int main(int argc,char *argv[]){
    //basic check
    if (argc !=2){
        return 1;
    }
    char *input = argv[1];
    //simple salt extraction, no need for cycle
    char salt[3];
    salt[0] = input[0];
    salt[1] = input[1];
    salt[2] = '\0';
    int pasLen = 5;
    //use cracker with different length of password until CRACK IT (or >5)
    for(int j =0; j <pasLen; j++){
        if(cracker(input, salt, 0, j) ==0){
            return 0;
        }
    }
    return 0;
}

//I chain return condition to pass "return 0" as fast as app found password

int cracker(char *input, char *salt, int k, int pasLenHere){
    for (int i =0; i<strlen(dict); i++){
        bruted[k] = dict[i];
        //lead me to the next bruted[k] char
        if(k<pasLenHere){
            if(cracker(input, salt, k+1, pasLenHere)==0){
                return 0;
            }
        }
        hash = crypt(bruted, salt);
        if (strcmp(hash, input) ==0){
            printf("%s\n", bruted);
            return 0;
        }
    }
    return 1;
}