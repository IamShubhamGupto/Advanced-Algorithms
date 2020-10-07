#include<stdio.h>
#include<stdlib.h>

int solve_matrix_chain(int* arr, int n){
    int** dp = (int**)malloc(sizeof(int*)*n);
    int i,j,k,l,res;
    for(i = 0; i < n; i++){
        dp[i] = (int*)malloc(sizeof(int)*n);
        for(j = 0; j < n; j++){
            dp[i][j] = 0;
        }
    }
    for(l = 2; l < n; l++){
        for(i = 1; i < n - l + 1; i++){
            j = i+l-1;
            if(j == n)
                continue;
            dp[i][j] = 9999999;
            for(k = i; k <= j-1; k++){
                res = dp[i][k] + dp[k+1][j] + arr[i-1]*arr[k]*arr[j];
                if(res < dp[i][j])
                    dp[i][j] = res;
            }
        }
    }
    int ans = dp[1][n-1];
    for(i = 0; i < n; i++){
        free(dp[i]);
    }
    free(dp);
    return ans;
}

int main(){
    int n;
    printf("Enter number of elements\n");
    scanf("%d",&n);
    //printf("")
    int* array = (int*)malloc(sizeof(int)*n);
    for(int i = 0; i < n; i++){
        scanf("%d",array+i);
    }
    int res = solve_matrix_chain(array, n);
    free(array);
    printf("Lowest cost = %d\n",res);
    return 0;
}