#include "../include/string.h"


void itoa(int num, char *str)
{
    int digit, i = 0;
    int len = len_num(num);

    if (num == 0) 
    {
        str[0] = '0';
        str[1] = '\0';
        return;
    }

    if (num < 0) 
    {
        i = 1; //first character will be a '-'.
        str[0] = '-';
        num = (-num); //turn the num into positive, and after add the minus.
    }
    
    //start looping from right to left, so we don't have to reverse the array later.
    for (int j = len + i - 1; j >= i; j--)
    {
        digit = num % 10;
        str[j] = digit + '0'; //convert the integer into its ascii representation.
        num /= 10;
    }
    str[len + i] = '\0';
}

int len_num(int num)
{
    int len = 0;
    while (num != 0)
    {
        num /= 10;
        len++;
    }
    return len;
}

int strlen(char string[])
{
    int count = 0;
    while (string[count] != '\0')
    {
        count++;
    }

    return count;
}




void append(char string[], char character)
{
    int len = strlen(string);
    string[len] = character;
    string[len+1] = '\0';
}