#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include "header.h"
#define DEBUG 1
void computeLPS(char* pattern, int m,int* lps){
    int len = 0;
    int i = 1;
    lps[0] = 0;
    while(i < m){
        if(pattern[i] == pattern[len]){
            len++;
            lps[i] = len;
            i++;
        }else{
            if(len != 0){
                len = lps[len-1];
            }else{
                lps[i] = 0;
                i++;
            }
        }
    }
}

int KMP(char* text, char* pattern){
    int n = strlen(text);
    int m = strlen(pattern);
    int* lps = (int*)malloc(sizeof(int)*m);
    int i;
    int j = 0;
    int prefix_length = 0;
    int max_prefix_length = 0;
    for(i = 0; i < m; i++){
        lps[i] = 0;
    }
    i = 0;
    computeLPS(pattern,m,lps);
    while(i < n){
        if(text[i] == pattern[j]){
            if(DEBUG){
                printf("Matched pattern j = %d, i = %d\n",j,i);
            }
            prefix_length++;
            i++;
            j++;
            if(DEBUG){
                printf("prefix_length = %d\n",prefix_length);
            }
            if(max_prefix_length < prefix_length){
                if(DEBUG)
                    printf("max_prefix_lnegth now is %d i = %d\n",prefix_length,i);
                max_prefix_length = prefix_length;
            }
        }
        if(j == m){
            return m;
        }else if(i < n && text[i] != pattern[j]){
            if(j != 0){
                j = lps[j-1];
                prefix_length -= j+1;
            }else{
                i++;
                
                prefix_length = 0;
            }
        }    
    }
    free(lps);
    return max_prefix_length;
}