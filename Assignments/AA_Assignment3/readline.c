#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define DEBUG 1
#define q 1000000007
/*
int main(){
    int T;
    char text1[1000];
    char text2[1000];
    int result;
    char* input;
    scanf(" %d",&T);
    int p;
    while(T--){
        result = 0;
        input = (char*)malloc(sizeof(char)*2002);
        scanf("%s",input);
        if(DEBUG){
            printf("input text %s\n",input);
        }
        p = 0;
        int len = strlen(input);
        if(len == 1 && (input[0] == ' ' || input[p] != '\0' || input[p] != '\n')){
            printf("%d",result);
            free(input);
            continue;
        }
        while(input[p] != ' ' && p < len){
            text1[p] = input[p];
            ++p;
        }
        text1[p] = '\0';
        int l = p;
        p+=1;
        while(p < len && input[p] != '\0' && input[p] != '\n' ){
            text2[p - l -1] = input[p];
            ++p;
        }
        if(p-l <= 1){
            text2[0] = '\0';
        }
        text2[p - l] = '\0';
        free(input);
        if(DEBUG){
            int l1 = strlen(text1);
            int l2 = strlen(text2);
            printf("text1 = %s text2 = %s l1 = %d l2 = %d \n",text1,text2,l1,l2);
        }
        if(strlen(text2) == 0){
            result = strlen(text1);
        }else{
            //result = solve(text1, text2);
        }
        printf("%d\n",result);
    }
    return 0;
}
*/

int main(){
    int T;
    char c;
    char text1[1000];
    char text2[1000];
    scanf("%d",&T);
    c = getchar_unlocked();
    while(T--){
        int i = 0;
        int first = 1;
        //int empty = 0;
        int len1 = 0;
        int len2 = 0;
        while(1){
            c = getchar_unlocked();
            if(DEBUG){
                printf("i = %d %c \n",i,c);
            }
            
            if(c != 0x0A){
                if(c == ' '){
                    first = 0;
                    text1[i]='\0';
                    len1 = i;
                    printf("l = %d\n",len1);
                }else if(first){
                    text1[i] = c;
                }else{
                    text2[i-len1-1] = c;
                }
            }else{
                len2 = i;
                text2[i-len1-1] = '\0';
                break;
            }
            ++i;  
        }
        
        if(i-len1 < 1){
            text1[0] = '\0';
        }
        if(i == len2){
            text2[len2] = '\0';
        }
        if(DEBUG){
            int l1 = strlen(text1);
            int l2 = strlen(text2);
            printf("text1 = %s text2 = %s l1 = %d l2 = %d \n",text1,text2,l1,l2);
        }
    }
    return 0;
}
