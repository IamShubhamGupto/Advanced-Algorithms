#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define DEBUG 0
#define q 1000000007
int compare_characters(char a, char b){
    if((a >= 65 && a <= 90) && (b >= 65 && b <= 90) && (a == b)){
        return 1;
    }else if((a >= 97 && a <= 122) && (b >= 97 && b <= 122) && (a == b)){
        return 1;
    }else if((a >= 65 && a <= 90) && (b >= 97 && b <= 122) && ((int)a + 32 == (int)b)){
        return 1;
    }else if((a >= 97 && a <= 122) && (b >= 65 && b <= 90) && ((int)a == (int)b + 32)){
        return 1;
    }
    return 0;
}
int get_minimum(int a, int b){
    if(a > b){
        return b;
    }
    return a;
}
int solve(const char text1[1000], const char text2[1000]){
    int l1 = strlen(text1);
    int l2 = strlen(text2);
    int i,j;
    int result;
    int** dp = (int**)malloc(sizeof(int*)*2);
    for(i = 0; i < 2; i++){
        dp[i] = (int*)malloc(sizeof(int)*(l1+1));
        for(j = 0; j <= l1; j++){
            if(i == 0){
                dp[i][j] = j;
            }else{
                dp[i][j] = 0;
            }
        }
    }
    for(i = 1; i <= l2; i++){
        for(j = 0; j <= l1; j ++){
            if(j == 0){
                dp[i%2][j] = i;
            }else if(compare_characters(text1[j-1],text2[i-1])){
                dp[i%2][j] = dp[(i-1)%2][j-1];
            }else{
                dp[i%2][j] = 1 + get_minimum(dp[(i - 1) % 2][j],get_minimum(dp[i % 2][j - 1], dp[(i - 1) % 2][j - 1]));
            }
        }
    }
    result = dp[l2 % 2][l1];
    for(i = 0; i < 2; i++){
        free(dp[i]);
    }
    free(dp);
    return result%q;

}
int main(){
    int T;
    char text1[1000];
    char text2[1000];
    int result;
    scanf("%d",&T);
    while(T--){
        scanf("%s %[^\n]",text1,text2);
        
        if(DEBUG){
            int l1 = strlen(text1);
            int l2 = strlen(text2);
            printf("%s %s %d %d \n",text1,text2,l1,l2);
        }
        result = solve(text1, text2);
        printf("%d\n",result);
    }
    return 0;
}