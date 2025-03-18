#ifndef STRING_H
#define STRING_H

char *itoa2(int num);
void itoa(int num, char *str);
int len_num(int num);
void append(char string[], char character);
int strlen(char string[]);
int strcmp(char string1[], char string2[]);
int strncmp(char string1[], char string2[], int bytes);


#endif