/*********************************************************************
* Author: Trever Fuhrer
* Created: 03/05/25
*
* This program implements two main methods, one to encrypt and one to decrypt
* Each works by adding the length of the string to the letter
* To get a different letter in the alphabet
**********************************************************************/

#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

/*
* Finds the length of a string
* input - string to get length of
* output - int length of the string
*/
int length(const char* str) {
    int length = 0;
    while (str[length] != '\0') {
        ++length;
    }
    return length;
}

/*
* Figures out wether a char is in alphabet or not
* input - char to check if in alphabet
* output - 1 if true or 0 if false
*/
int myIsAlpha(char ch) {
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

/*
* Encrypts each letter in a string
* input - string to be encrypted
* output - encrypted string
*/
char* encrypt(const char* str) {
    int len = length(str);

    if (len < 2 || len > 20) return NULL;

    char* str2 = (char*)malloc(len + 1);
    if (!str2) return NULL;

    for (int i = 0; i < len; ++i) {
        if (myIsAlpha(str[i])) {
            // Cycle to start of alphabet if need be
            if (str[i] >= 'A' && str[i] <= 'Z') {
                str2[i] = 'A' + (str[i] - 'A' + len) % 26;
            } 
            else if (str[i] >= 'a' && str[i] <= 'z') {
                str2[i] = 'a' + (str[i] - 'a' + len) % 26;
            }
        } 
        else {
            str2[i] = str[i];
        }
    }
    str2[len] = '\0';
    return str2;
}

/*
* Decrypts each letter in a string
* input - string to be decrypted
* output - decrypted string
*/
char* decrypt(const char* str) {
    int len = length(str);
    
    if (len < 2 || len > 20) return NULL;

    char* str2 = (char*)malloc(len + 1);
    if (!str2) return NULL;

    for (int i = 0; i < len; ++i) {
        if (myIsAlpha(str[i])) {
            // Cycle to start of alphabet if need be
            if (str[i] >= 'A' && str[i] <= 'Z') {
                str2[i] = 'A' + (str[i] - 'A' - len + 26) % 26;
            } 
            else if (str[i] >= 'a' && str[i] <= 'z') {
                str2[i] = 'a' + (str[i] - 'a' - len + 26) % 26;
            }
        } 
        else {
            str2[i] = str[i];
        }
    }
    str2[len] = '\0';
    return str2;
}