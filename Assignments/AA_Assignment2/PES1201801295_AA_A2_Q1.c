#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define DEBUG 0

static int find_min_rotations(char*, char*);
static void compute_lps_table(char* , int ,int* );
/*  *
    * Fills an array Longest Proper Suffix based on position of characters in pattern
    * @params: pattern: search pattern entered by user
    *          m: length of pattern
    *          lps: an array of integers holding positions of last known index of pattern[i], by default 0
    * @return: void 
*/
static void compute_lps_table(char* pattern, int m,int* lps){
    int len = 0;
    int i = 1;
    lps[0] = 0;
    while(i < m){
        if(pattern[i] == pattern[len]){
            len++;
            lps[i] = len;
            i++;
        }else if(len != 0){
            len = lps[len-1];
        }else{
            lps[i] = 0;
            i++;
        }
        
    }
}
/*  *
    * Finds the minimum number of rotations to be applied on text such that both text and pattern have the longest prefix
    * @params: text: text to be rotated by program
    *          pattern: pattern to be searched
    * @return: [integer] least number of rotations required  
*/
static int find_min_rotations(char* text, char* pattern){
    int n = strlen(text);
    int m = strlen(pattern);
    int* lps = (int*)malloc(sizeof(int)*m);
    int i;
    int pattern_i = 0;
    int max_prefix_length = 0;
    for(i = 0; i < m; i++){
        lps[i] = 0;
    }
    i = 0;
    int min_rotations = 0;
    compute_lps_table(pattern,m,lps);
    while(i < n){
        if(text[i] == pattern[pattern_i]){
            if(DEBUG){
                printf("Matched pattern pattern_i(prefix_length) = %d, i = %d\n",pattern_i,i);
            }
            i++;
            pattern_i++;    
        }
        if(pattern_i == m){
            if(DEBUG){
                printf("[j==m] full string match\n");
            }
            max_prefix_length = m;
            min_rotations = (i-pattern_i)%(n/2);
            break;
        }else if(i < n && text[i] != pattern[pattern_i]){
            if(max_prefix_length < pattern_i){
                if(DEBUG)
                    printf("max_prefix_length now is %d i = %d\n",pattern_i,i);
                max_prefix_length = pattern_i;
                min_rotations = (i-pattern_i)%(n/2);
            }
            if(pattern_i != 0){
                pattern_i = lps[pattern_i-1];
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
    if(n <= 0){
        printf("0\n");
        exit(0);
    }
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
    int result = find_min_rotations(text,pattern);
    printf("%d\n",result);
    free(pattern);
    free(text);
    return 0;
}