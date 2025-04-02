#include "../include/string.h"
#include "../../drivers/include/screen.h"

#define MAX_STR_LEN 30

char* itoa2(int num)
{
    int digit, i = 0;
    int len = len_num(num);
    static char string[MAX_STR_LEN];

    if (num == 0) 
    {
        string[0] = '0';
        string[1] = '\0';
        return string;
    }

    if (num < 0) 
    {
        i = 1; //first character will be a '-'.
        string[0] = '-';
        num = (-num); //turn the num into positive, and after add the minus.
    }
    
    //start looping from right to left, so we don't have to reverse the array later.
    for (int j = len + i - 1; j >= i; j--)
    {
        digit = num % 10;
        string[j] = digit + '0'; //convert the integer into its ascii representation.
        num /= 10;
    }
    string[len + i] = '\0';

    return string;
}


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

//return 0 if the strings are equal, if not return -1.
int strcmp(char string1[], char string2[])
{
    //if the length of the strings are not equal return -1.
    if (strlen(string1) != strlen(string2)) {return -1;}

    //length of both strings
    int len = strlen(string1);

    for (int i = 0; i < len; i++)
    {
        if (string1[i] != string2[i])
        {
            return -1;
        }
    }

    return 0;
}

int strncmp(char string1[], char string2[], int bytes)
{
    
    //check if one of the strings length is smaller then bytes
    if (strlen(string1) < bytes || strlen(string2) < bytes) {return -1;}

    for (int i = 0; i < bytes; i++)
    {
        if (string1[i] != string2[i])
        {
            return -1;
        }
    }

    return 0;
}

void print_hex(int num) {
    char hex_chars[] = "0123456789ABCDEF";
    char buf[9]; // To hold 8 hex digits + null terminator
    buf[8] = '\0'; // Null-terminate the string

    for (int i = 7; i >= 0; i--) {
        buf[i] = hex_chars[num % 16];
        num /= 16;
    }

    print(buf); // Call the print function to display the hex string
}
