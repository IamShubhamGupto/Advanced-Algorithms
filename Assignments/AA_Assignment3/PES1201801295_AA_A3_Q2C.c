#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define DEBUG 0
#define q 1000000007
int compare_characters(const int a, const int b){
    int d_a = a - 96;;
    int d_b = b - 96;
    if(a >=65 && a <= 90){
        d_a  = a - 64;
    }
    if(b >=65 && b <= 90){
        d_b  = b - 64;
    }
    return abs(d_a-d_b);
}
int get_minimum(const int a, const  int b){
    if(a > b){
        return b;
    }
    return a;
}
int get_position(const int c){
    if(c >= 65 && c <= 90){
        return c - 64;
    }
    return c - 96;
}
void display_table( long long int**dp, const int l1,const int l2){
    for(int i = 0; i < 2; i++){
        for(int j = 0; j <= l2; j++){
            printf("%lld ",dp[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int solve(const char text1[1001], const char text2[1001]){
    int l1 = strlen(text1);
    int l2 = strlen(text2);
    int i,j,a,b;
    long long int result;
    long long int** dp = (long long int**)malloc(sizeof(long long int*)*2);
    int cost = 1;
    for(i = 0; i < 2; i++){
        dp[i] = (long long int*)malloc(sizeof(long long int)*(l2+1));
        dp[0][0] = 0;
        for(j = 1; j <= l2; j++){
            if(i == 0){
                dp[i][j] = dp[i][j-1] + get_position(text2[j-1]);
            }else{
                dp[i][j] = 0;
            }
        }
    }
    //display_table(dp,l1,l2);  

    for(i = 1; i <= l1; i++){
        dp[i%2][0] = dp[(i-1)%2][0] + get_position(text1[i-1]);
        for(j = 1; j <= l2; j++){
            cost = compare_characters(text1[i-1],text2[j-1]);
            dp[i%2][j] = get_minimum(dp[(i - 1) % 2][j]%q + get_position(text1[i-1]), 
                get_minimum(dp[(i - 1)% 2][j - 1]%q + cost%q, dp[i % 2][j - 1]%q+ get_position(text2[j-1])));
        }
        //display_table(dp,l1,l2);  
    }
    
    if(DEBUG){
        display_table(dp,l1,l2);
    }
    result = dp[l1%2][l2];
    for(i = 0; i < 2; i++){
        free(dp[i]);
    }
    free(dp);
    return result%q;

}
int main(){
    int T;
    char text1[1001];
    char text2[1001];
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

/*
int main(){
    int T;
    char c;
    char text1[1001];
    char text2[1001];
    int i;
    int first;
    int len1;
    int len2;
    long long int result = 0;
    text1[0] = '\0';
    text2[0] = '\0';
    scanf("%d",&T);
    c = getchar();
    while(T--){
        i = 0;
        first = 1;
        len1 = 0;
        len2 = 0;
        while(1){
            c = getchar();
            if(c != 0x0A){
                if(c == ' '){
                    first = 0;
                    text1[i]='\0';
                    len1 = i; 
                }else if(first){
                    text1[i] = c;
                }else{
                    text2[i-len1-1] = c;
                }
            }else{
                len2 = i-len1-1;
                text2[i-len1-1] = '\0';
                break;
            }
            if(DEBUG){
                printf("i = %d %c \n",i,c);
                printf("len1 = %d\n",len1);
            }
            ++i;  
        }
        if(i-len1 < 1){
            text1[0] = '\0';
        }
        if(len2 <= 0){
            text2[0] = '\0';
            len2 = 0;
        }
        if(DEBUG){
            printf("text1 = %s text2 = %s l1 = %d l2 = %d \n",text1,text2,len1,len2);
        }
        if(len1 == 0){
            result = len2;
        }else if(len2 == 0){
            result = len1;
        }else{
            result = solve(text1,text2);
        }
        printf("%lld\n",result);

    }
    return 0;
}
*/