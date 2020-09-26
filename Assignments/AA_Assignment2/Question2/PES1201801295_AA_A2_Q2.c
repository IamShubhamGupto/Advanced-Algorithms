#include<stdio.h>
#include<stdlib.h>

#define d 31
#define q 1000000007
#define DEBUG 1
static void fill_hash_table(char* pattern, long long int* hash_table);

static void fill_hash_table(char* pattern, long long int* hash_table){
    long long int temp = 1;
    int m = strlen(pattern);
    int i;
    for(i = 1; i <= m; i++){
        temp = (temp*d)%q;
        hash_table[i] = (hash_table[i-1]%q + ((long long int)(97 - pattern[i-1] + 1)*temp)%q)%q;
    }
}
int main(){
    int n;
    int number_of_queries;
    int division;
    int i;
    scanf("%d",&n);
    char* text = (char*)malloc(sizeof(char)*(n+1));
    scanf("%s",text);
    text[n] = '\0';
    //do preprocessing
    long long int* hash_table = (long long int*)malloc(sizeof(long long int)*(n+1));
    for(i = 0; i < n+1; i++){
        hash_table[i] = 0;
    }
    fill_hash_table(text,hash_table);
    scanf("%d",&number_of_queries);
    for(i = 0; i < number_of_queries; i++){
        scanf("%d",&division);
        division -= 1;

    }
    free(hash_table);
    return 0;
}