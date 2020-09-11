#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "header.h"
void readTextAndPattern(char* text, char* pattern){
    int n,m;
    printf("Enter size of text\n");
    scanf("%d",&n);
    text = (char*)malloc(sizeof(char)*(n+1));

    initialize_string(text,n);
    printf("Enter text\n");
    scanf("%s",text);
    text[n] = '\0';

    printf("\nEnter size of pattern \n");
    scanf("%d",&m);
    pattern = (char*)malloc(sizeof(char)*(m+1));
                
    initialize_string(pattern,m);
    printf("Enter pattern\n");

    scanf("%s",pattern);
    pattern[m] = '\0';
}
void initialize_string(char* string, int m){
    for(int i = 0; i < m; i++){
        string[i] = '0';
    }
    string[m] = '\0';
}
int NaiveString(char* text, char* pattern){
    int n = strlen(text);
    int m = strlen(pattern);
    if ( m > n)
        return -1;
    for(int i = 0; i < n; i++){
        int j;
        for(j = 0; i < m; j++){
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
    int n = strlen(text);
    int m = strlen(pattern);
    if ( m > n)
        return -1;
    int i = 0;
    while(i < n){
        int j;
        for(j = 0; j < m; j++){
            if(text[i+j] != pattern[j])
                break;
        }
        if(j == 0){
            i++;
        }else if(j == m){
            return i;
        }else{
            i += j;
        }
    }
    return -1;    
}
int RabinKarp(char* text, char* pattern, int q){
    int n = strlen(text);
    int m = strlen(pattern);
    int i;
    int j;
    int p_hash = 0;
    int t_hash = 0;
    int h = 1;
    int d = 256; //radix

    for(i = 0; i < m-1; i++){
        h = (h*d)%q;
    }
    for(i = 0; i < m; i++){
        p_hash = (p_hash*d + (int)pattern[i])%q;
        t_hash = (t_hash*d + (int)text[i])%q;
    }
    for(i = 0; i <= n-m; i++){
        if(p_hash == t_hash){
            for(j = 0; j < m; j++){
                if(text[i+j] != pattern[j])
                    break;
            }
            if(j == m){
                return i;
            }
        }
        if(i < n-m){
            t_hash = (d*(t_hash - (int)text[i]*h) + (int)text[i+m])%q;
            if(t_hash < 0)
                t_hash += q;
        }
    }
    return -1;
}