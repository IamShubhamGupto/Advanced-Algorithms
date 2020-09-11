#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "header.h"
void initialize_string(char* string, int m){
    for(int i = 0; i < m; i++){
        string[i] = '0';
    }
    string[m] = '\0';
}
int NaiveString(char* text, char* pattern){
    int m = strlen(text);
    int n = strlen(pattern);
    for(int i = 0; i < m; i++){
        int j;
        for(j = 0; i < n; j++){
            if(text[i+j] != pattern[j]){
                break;
            }

        }
        if(j == n){
            return i;
        }
    }
    return -1;

}