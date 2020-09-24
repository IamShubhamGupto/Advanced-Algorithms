#include<stdio.h>
#include<stdlib.h>
void solveCoinRow(int* array, int n);

void solveCoinRow(int* array, int n){
    int* dp = (int*)malloc(sizeof(int)*(n+1));
    for(int i = 0; i <= n; i++)
        dp[i] = 0;
    dp[1] = array[0];
    //optimal value
    for(int i = 2; i <= n+1; i++){
        int val = array[i-1] + dp[i-2];
        if (val > dp[i-1]){
            dp[i] = val;
        }else{
            dp[i] = dp[i-1];
        }
        
        //dp[i+1] = array[i] + dp[i-1] > dp[i] ? array[i] + dp[i-1] : dp[i];
    }
    printf("%d",dp[n]);
}
int main(){
    int n;
    scanf("%d",&n);
    int* array = (int*)malloc(sizeof(int)*n);
    for(int i = 0; i < n; i++){
        scanf("%d",(array+i));
    }
    solveCoinRow(array,n);
    return 0;
 }