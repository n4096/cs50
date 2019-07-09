#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    long cardNum = get_long("Gimmi: ");
    int result;
    bool switcher = true;
    char *resultType;
    long cardDigitNum = cardNum;
    int counter = 0;
    while(cardDigitNum>0){
        cardDigitNum = cardDigitNum/10;
        counter ++;
    }
    while (cardNum>0){
        if(switcher){
            result = result + cardNum%10;
            switcher = false;
        }
        else{
            result = result + ((cardNum%10) * 2)%10 + ((cardNum%10) * 2)/10;
            switcher = true;
        }
        if(cardNum<100&&cardNum>=10){
            if(cardNum/10 == 4&&(counter==13||counter==16)){
                resultType = "VISA";
            }
            else if((cardNum==51||cardNum==52||cardNum==53||cardNum==54||cardNum==55)&&counter==16){
                resultType = "MASTERCARD";
            }
            else if ((cardNum==37||cardNum==34)&&(counter==15)){
                resultType = "AMEX";
            }
            else{
                resultType = "INVALID";
            }
        }
        
        cardNum = cardNum/10;
    }
    if(result%10==0){
        printf("%s\n",resultType);
    }
    else{
        printf("INVALID\n");
    }

    return 0;
    // char *cardNum;
    // int value;
    // int result = 0;
    // for (int i = strlen(cardNum)-2; i >= 0; i = i - 2){
    //     value = (cardNum[i] - '0')*2;
    //     value = value%10+value/10;
    //     result = result+value;
    // }
    // for (int i = strlen(cardNum)-1; i >= 0; i = i - 2){
    //     result = result + (cardNum[i] - '0');
    // }
    // printf("result: %i",result);
    // return 0;
}

//        value = strtol(cardNum[i],&ptr , 10);