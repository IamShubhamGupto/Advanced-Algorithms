#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "header.h"
int main(){
    printf("------------------------\nSelect a algorithm\nNaive String - 1\nModified Naive String - 2\nRobin Karp - 3\nKMP -4\n");
    printf("------------------------\n");
    int choice;
    int m;
    int n;
    int flag = 1;
    //int i;
    scanf("%d",&choice);
    while(flag && choice >= 1 && choice <= 4){
        switch(choice){
            case 1:
                printf("Enter size of text\n");
                scanf("%d",&m);
                char* text = (char*)malloc(sizeof(char)*(m+1));
                initialize_string(text,m);
                printf("Enter text\n");
                /*
                for(i = 0; i < m; i++){
                    scanf("%c",&text[i]);
                }
                */
                scanf("%s",text);
                text[m] = '\0';
                printf("\nEnter size of pattern\n");
                scanf("%d",&n);
                char* pattern = (char*)malloc(sizeof(char)*(n+1));
                initialize_string(pattern,n);
                printf("Enter pattern\n");
                /*
                for(i = 0; i < n; i++){
                    scanf("%c",&pattern[i]);
                }
                */
                scanf("%s",pattern);
                pattern[n] = '\0';
                int result = NaiveString(text,pattern);
                printf("------------------------\nPattern occurs at %d th index\n------------------------\n",result);
                free(text);
                free(pattern);
                break;
            case 2:
                //ModNaiveString();
                break;
            case 3:
                //RobinKarp();
                break;
            case 4:
                //KMP();
                break;
            default: flag = 0;    
        }
        printf("------------------------\nSelect a algorithm\nNaive String - 1\nModified Naive String - 2\nRobin Karp - 3\nKMP -4\n");
        printf("------------------------\n");
        scanf("%d",&choice);
    }
    return 0;
}