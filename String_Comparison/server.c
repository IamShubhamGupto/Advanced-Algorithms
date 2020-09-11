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
    if (n > m)
        return -1;
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
int ModNaiveString(char* text, char* pattern){
    int m = strlen(text);
    int n = strlen(pattern);
    if (n > m)
        return -1;
    int i = 0;
    while(i < m){
        int j;
        for(j = 0; j < n; j++){
            if(text[i+j] != pattern[j])
                break;
        }
        if(j == 0){
            i++;
        }else if(j == n){
            return i;
        }else{
            i += j;
        }
    }
    return -1;    
}