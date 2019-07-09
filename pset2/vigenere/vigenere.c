#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Usage: one and only one arg");
        return 1;
    }

    char *key = argv[1];

    for (int i=0; i<strlen(key); i++){
        if(!isalpha(key[i])){
            printf("Usage: only alpha-numeric-values");
            return 1;
        }
    }
    
    char *plaintext = get_string("Plaintext:");
    char ciphertext[strlen(plaintext)]; 
    int keyLen = strlen(key);
    int count = 0;
    
    for(int j = 0; j<keyLen;j++){
        key[j]=toupper(key[j]);
    }
    for(int i = 0; i<strlen(plaintext); i++){
        char thisChar = plaintext[i];
        //check if alphabet char, basically
        if(isalpha(thisChar)){
            int k;
            //doing key repetition for any length of plaintext
            if(i>=keyLen){
                k = (i-count)%keyLen;
            }
            else{
                k=i;
            }
            // -65 to get 0 out of A etc
            int test = thisChar + key[k] - 65;
            //this is for lowerCase that went too far
            while (test>90&&thisChar<=90){
                test = test - 26;
            }
            //this is for upperCase that went too far
            while (test>122&&thisChar>=97){
                test = test - 26;
            }
            plaintext[i] = test;
        }
        else{
            plaintext[i] = thisChar;
            count++;
        }
    }
    printf("ciphertext:%s\n", plaintext);
    
    return 0;
}
//first try. Later I tried to refactor it a little bit, but in the end I wasn't able to get rid of count 
    // for(int i = 0; i<strlen(plaintext); i++){
    //     //check if symbol A-Z or a-z
    //     if(plaintext[i]>=65 && plaintext[i]<=90){
    //         //
    //         int j;
    //         if(i>=keyLen){
    //             j = i%keyLen;
    //         }
    //         else{
    //             j = i;
    //         }
    //         plaintext[i]=plaintext[i] + key[j]-65;
    //         if(plaintext[i]>90){
    //             plaintext[i]=plaintext[i] - 26;
    //         }
    //     }
    //     else if(plaintext[i]>=97 && plaintext[i]<=122){
    //         //
    //         int j;
    //         if(i>=keyLen){
    //             j = (i- count)%(keyLen);
    //         }
    //         else{
    //             j = i - count;
    //         }
    //         plaintext[i] = plaintext[i] + key[j] -32 -65;
    //         if(plaintext[i]>90){
    //             plaintext[i]=plaintext[i] - 26 + 32;
    //         }
    //         else{
    //             plaintext[i]=plaintext[i] + 32;
    //         }
    //     }
    //     else{
    //         count++;
    //     }
    // }
    
    
    // printf("ciphertext:%s\n", plaintext);
    
    
    
    
//    printf("%s is %i chars\n",key, keyLen);
    // for (int i = 0; i < strlen(key); i++){
    //     argv[i]
    // }
