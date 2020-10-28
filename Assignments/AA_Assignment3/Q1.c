#include<stdio.h>
#include<stdlib.h>

#define DEBUG 0

int main(){
    int T,N,K;
    int MAX_N = 0;
    int MAX_K = 0;
    scanf("%d",&T);
    int* N_values =(int*)malloc(sizeof(int)*T);
    int* K_values = (int*)malloc(sizeof(int)*T);
    int temp = T;
    int i,j,k;
    
    while(T--){
        scanf("%d %d",N_values+temp-T-1,K_values + temp - T-1);
        if(DEBUG){
            printf("N = %d K = %d\n",N_values[temp-T-1],K_values[temp-T-1]);
        }
        if(MAX_N < N_values[temp-T-1]){
            MAX_N = N_values[temp-T-1];
        }
    }
    MAX_K = MAX_N/4;
    if(MAX_N%4 == 1){
        ++MAX_K;
    }
    int*** dp = (int***)malloc(sizeof(int**)*MAX_N);
    for(i = 0; i < MAX_N; i++){
        dp[i] = (int**)malloc(sizeof(int*)*MAX_K);
        for(j = 0; j < MAX_K; j++){
            dp[i][j] = (int*)malloc(sizeof(int)*4);
            for(k = 0; k < 4; k++){
                dp[i][j][k] = 0;
            }
        }
    }
    for(i = 0; i < MAX_N; i++){
        //dp[i] = (int**)malloc(sizeof(int*)*MAX_K);
        for(j = 0; j < MAX_K; j++){
            //dp[i][j] = (int*)malloc(sizeof(int)*4);
            free(dp[i][j]);
        }
        free(dp[i]);
    }
    free(dp);
    free(N_values);
    free(K_values);
    return 0;
}