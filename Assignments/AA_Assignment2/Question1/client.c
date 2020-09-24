#include<stdio.h>
#include<stdlib.h>
//#include<string.h>
#include "header.h"
#define DEBUG 1
 int main(){
    int n;
    int i = 0;
    scanf("%d",&n);
    char* pattern = (char*)malloc(sizeof(char)*(n+1));
    char* text = (char*)malloc(sizeof(char)*(2*n+1));
    scanf("%s",pattern);
    pattern[n] = '\0';
    scanf("%s",text);
    for(i = n; i < 2*n; i++){
        text[i] = text[i-n];
    }
    text[i] = '\0';
    if(DEBUG){
        printf("Text = %s\n",text);
        printf("Pattern = %s\n",pattern);
    }
    int result = KMP(text,pattern);
    printf("%d\n",result);
    free(pattern);
    free(text);
    return 0;
 }