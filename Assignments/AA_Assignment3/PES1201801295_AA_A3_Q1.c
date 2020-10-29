#include<stdio.h>
#include<stdlib.h>

#define DEBUG 0
#define q 1000000007
long long int get_sum(long long int* arr){
    long long int sum = 0;
    for(int i = 0; i < 5; i++){
        sum = (sum%q + arr[i]%q)%q;
    }
    return sum;
}
void display_table(long long int ***dp){
    for(int i = 0; i <= 4; i++){
        for(int j = 0; j <= 4; j++){
            for(int k = 0; k < 5; k++){
                printf("%lld ",dp[i][j][k]);
            }
            printf("\n");
        }
        printf(" ");
    }
}

int main(){
    int T,N,K;
    int i,j,k;
    long long int result = 0;
    long long int*** dp = (long long int***)malloc(sizeof(long long int**)*(200+1));
    for(i = 0; i <= 200; i++){
        dp[i] = (long long int**)malloc(sizeof(long long int*)*(200+1));
        for(j = 0; j <= 200; j++){
            dp[i][j] = (long long int*)malloc(sizeof(long long int)*5);
            for(k = 0; k < 5; k++){
                dp[i][j][k] = 0;
            }
        }
    }
    
    
    dp[1][0][0] = 25;
    dp[1][0][1] = 1;
    //(24*get_sum(dp[i-1][j-1]))%q
    for(i = 2; i <= 200; i++){
        for(j = 0; j <= 200; j++){
            dp[i][j][0] = ((25%q*dp[i-1][j][0]%q)%q + (24%q*dp[i-1][j][1]%q)%q + 
                (24*dp[i-1][j][2]%q)%q + (25*dp[i-1][j][3]%q)%q + (24*dp[i-1][j][4]%q) + q)%q;
            
            dp[i][j][1] = (dp[i-1][j][0]%q + dp[i-1][j][1]%q + dp[i-1][j][2]%q + dp[i-1][j][4]%q + q)%q;

            dp[i][j][2] = (dp[i-1][j][1]%q + dp[i-1][j][4]%q + q)%q;

            dp[i][j][3] = (dp[i-1][j][2]%q +q )%q;

            dp[i][j][4] = (j > 0)? dp[i-1][j-1][3]%q : 0;
            
        }
    }
    if(DEBUG){
        display_table(dp);
    }

    scanf("%d",&T);
    int temp = T;
    while(T--){
        scanf("%d %d",&N,&K);
        if(DEBUG){
            printf("N = %d K = %d\n",N,K);
        }
        result = get_sum(dp[N][K]);
        printf("%lld\n",result);
    }
    for(i = 0; i <= 200; i++){
        //dp[i] = (int**)malloc(sizeof(int*)*MAX_K);
        for(j = 0; j <= 200; j++){
            //dp[i][j] = (int*)malloc(sizeof(int)*4);
            free(dp[i][j]);
        }
        free(dp[i]);
    }
    free(dp);
    return 0;
}