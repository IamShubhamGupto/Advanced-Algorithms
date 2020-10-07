#include<stdio.h>
#include<stdlib.h>

void solve_rod_cutting(int* cost, int* dp, int n){
    int i,j, max_val;
    for(i = 1; i <= n; i++){
        max_val = -9999999;
        for(j = 0; j < i; j++){
            max_val = max_val > cost[j] + dp[i-j-1]? max_val: cost[j] + dp[i-j-1];
        }
        dp[i] = max_val;
    }
    printf("maximum rod cutting value = %d\n",dp[n]);
}
int main(){
    printf("Enter length of rod\n");
    int n;
    int i;
    scanf("%d",&n);
    int* cost = (int*)malloc(sizeof(int*)*n);
    int* dp = (int*)malloc(sizeof(int)*(n+1));
    for(i = 0; i < n; i++){
        dp[i] = 0;
        printf("Enter cost of rod length %d\n",i+1);
        scanf("%d",cost+i);
    }
    dp[i] = 0;
    solve_rod_cutting(cost,dp,n);
    free(cost);
    free(dp);
    return 0;
}