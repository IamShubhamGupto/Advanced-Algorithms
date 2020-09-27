#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define DEBUG 0

int KMP(char*, char*);
void computeLPS(char* , int ,int* );

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
    int max_prefix_length = 0;
    for(i = 0; i < m; i++){
        lps[i] = 0;
    }
    i = 0;
    int min_rotations = n+1;
    computeLPS(pattern,m,lps);
    while(i < n){
        if(text[i] == pattern[j]){
            if(DEBUG){
                printf("Matched pattern j(prefix_length) = %d, i = %d\n",j,i);
            }
            i++;
            j++;
            
        }
        if(j == m){
            if(DEBUG){
                printf("[j==m] full string match\n");
            }
            max_prefix_length = m;
            min_rotations = (i-j)%(n/2);
            break;
        }else if(i < n && text[i] != pattern[j]){
            if(max_prefix_length < j){
                if(DEBUG)
                    printf("max_prefix_length now is %d i = %d\n",j,i);
                max_prefix_length = j;
                min_rotations = (i-j)%(n/2);
            }
            if(j != 0){
                j = lps[j-1];
            }else{
                i++;
            }
        }    
    }
    free(lps);
    return min_rotations;
}
int main(){
    int n;
    int i = 0;
    scanf("%d",&n);
    if(n <= 0)
        exit(0);
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
        printf("[main] Text = %s\n",text);
        printf("[main] Pattern = %s\n",pattern);
    }
    int result = KMP(text,pattern);
    printf("%d\n",result);
    free(pattern);
    free(text);
    return 0;
}