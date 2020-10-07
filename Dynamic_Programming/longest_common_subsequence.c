#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int solve_lcs(char* text, char* pattern){
    int m = strlen(text);
    int n = strlen(pattern);
    int i,j;
    int** dp = (int**)malloc(sizeof(int*)*(m+1));
    for(i = 0; i <= m; i ++){
        dp[i] = (int*)malloc(sizeof(int)*(n+1));
        for(j = 0; j <= n; j++){
            dp[i][j] = 0;
        }
    }
    for(i = 1; i <= m; i++){
        for(j = 1; j <=n; j++){
            if(text[i-1] == pattern[j-1]){
                dp[i][j] = dp[i-1][j-1] + 1;
            }else{
                dp[i][j] = dp[i-1][j] > dp[i][j-1] ? dp[i-1][j]: dp[i][j-1];
            }
        }
    }
    int ans = dp[m][n];
    for(i = 0; i <= m; i++){
        free(dp[i]);
    }
    free(dp);
    return ans;
}

int main(){
    int n,m,i,j;
    scanf("%d",&n);
    char* text = (char*)malloc(sizeof(char)*(n+1));
    scanf("%s",text);
    text[n] = '\0';
    scanf("%d",&m);
    char* pattern = (char*)malloc(sizeof(char)*(m+1));
    scanf("%s",pattern);
    int res = solve_lcs(text, pattern);
    printf("Longest common subsequence = %d\n",res);
    free(pattern);
    free(text);
    return 0;
}