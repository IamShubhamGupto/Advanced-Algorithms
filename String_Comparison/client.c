#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "header.h"
#define DEBUG 0
int main(){
    char choice;
    int m;
    int n;
    int flag = 1;
    char* text;
    char* pattern;
    int result;
    while(flag){
        printf("------------------------\nSelect a algorithm\nNaive String - 1\nModified Naive String - 2\nRobin Karp - 3\nKMP - 4\n------------------------\n");
        scanf(" %c",&choice);
        printf("Enter size of text\n");
        scanf("%d",&n);
        text = (char*)malloc(sizeof(char)*(n+1));

        initialize_string(text,n);
        printf("Enter text\n");
        scanf("%s",text);
        text[n] = '\0';

        printf("\nEnter size of pattern\n");
        scanf("%d",&m);
        pattern = (char*)malloc(sizeof(char)*(m+1));

        initialize_string(pattern,m);
        printf("Enter pattern\n");

        scanf("%s",pattern);
        pattern[m] = '\0';
        switch(choice){
            case '1':
                if(DEBUG){
                    printf("Algorithm 1\n");
                }
                
                result = NaiveString(text,pattern);
                printf("------------------------\nPattern occurs at %d th index\n------------------------\n",result);
                free(text);
                free(pattern);
                break;
            case '2':
            
                if(DEBUG){
                    printf("Algorithm 2\n");
                    printf("%s\n%s\n",text,pattern);
                }
                result = ModNaiveString(text,pattern);
                printf("------------------------\nPattern occurs at %d th index\n------------------------\n",result);
                free(text);
                free(pattern);
                //ModNaiveString();
                break;
            case '3':
                if(DEBUG){
                    printf("Algorithm 3\n");
                    printf("%s\n%s\n",text,pattern);
                }
                printf("Enter a prime number\n");
                int q;
                scanf("%d",&q);
                result = RabinKarp(text,pattern,q);
                printf("------------------------\nPattern occurs at %d th index\n------------------------\n",result);
                free(text);
                free(pattern);
                break;
            case '4':
                if(DEBUG){
                    printf("Algorithm 4\n");
                }
                result = KMP(text,pattern);
                printf("------------------------\nPattern occurs at %d th index\n------------------------\n",result);
                free(text);
                free(pattern);
                break;
            default: flag = 0;    
        }
        
    }
    return 0;
}