#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define d 31
#define q 1000000007
#define DEBUG 0

static void fill_hash_table(char* , long long int* , long long int*);
static int find_longest_prefix(long long int* , long long int* , int , int);
/*  *
    * Finds the longest prefix in subtrings B and C using Binary Search on the hash table
    * @params: hash_table: array of hashes of prefixes of pattern
    *          pow_table: array of powers of d
    *          division: 1 based index where the B and C substring are divided
    *          length_of_hashtable: length of hash_table
    * @return: [integer] longest common prefix found in substring B and C 
*/
static int find_longest_prefix(long long int* hash_table, long long int* pow_table, int division, int length_of_hashtable){
    long long int l_val;
    long long int r_val;
    int longest_prefix_set = 1;
    int longest_prefix_not_set = division + 1;
    int max_val = 0;
    while(longest_prefix_set < longest_prefix_not_set){
        
        int mid = longest_prefix_set + (longest_prefix_not_set - longest_prefix_set)/2;
        l_val = (hash_table[longest_prefix_set]*pow_table[division])%q;
        if(division + longest_prefix_set > length_of_hashtable){
            r_val = (hash_table[length_of_hashtable]%q - hash_table[division]%q +q)%q;
        }else{
            r_val = (hash_table[division+longest_prefix_set]%q - hash_table[division]%q +q)%q;
        }
        
        if(DEBUG){
            printf("[find_longest_prefix] longest prefix set = %d longest prefix not set = %d\n",longest_prefix_set,longest_prefix_not_set);
            printf("[find_longest_prefix] mid = %d\n",mid);
            printf("[find_longest_prefix] l val = %d r val = %d\n",l_val,r_val);
        }
        if(l_val == r_val && max_val < longest_prefix_set){
            if(DEBUG){
                printf("[find_longest_prefix] Inside if\n");
            }
            max_val = longest_prefix_set;
            longest_prefix_set = mid;
        }else{
            if(DEBUG){
                printf("[find_longest_prefix] Inside else\n");
            }
            longest_prefix_not_set = longest_prefix_set;
            longest_prefix_set = max_val + (longest_prefix_set-max_val)/2; 
        }
    }
    return max_val;
}
/*  *
    * Fills the hash table and the power table - stores values of (d^i)%q for i in [0, length of string]
    * hash table pseudo code:
    *    hash_table[i] = (hashtable[i-1]%q + (integer position of character pattern[i-1]xpow_table[i-1])%q)%q
    * @params: pattern: text input by user
    *          hash_table: array of hashes of prefixes of pattern
    *          pow_table: array of powers of d
    * @return: void 
*/
static void fill_hash_table(char* pattern, long long int* hash_table, long long int* pow_table){
    long long int temp = 1;
    int m = strlen(pattern);
    int i;
    hash_table[0] = 0;
    pow_table[0] = temp;
    for(i = 1; i <= m; i++){
        temp = (temp*d)%q;
        pow_table[i] = temp;
        hash_table[i] = (hash_table[i-1]%q + (((int)pattern[i-1] - 96)*pow_table[i-1])%q)%q;
    }

    if(DEBUG){
        printf("[fill_hash_table] pow_table = \n");
        for(i = 0; i <= m; i++){
            printf("%d ",pow_table[i]);
        }
        printf("\n");

        printf("[fill_hash_table] hash_table = \n");
        for(i = 0; i <= m; i++){
            printf("%llu ",hash_table[i]);
        }
        printf("\n");
    }
}
int main(){
    int n;
    int number_of_queries;
    int division;
    int i;

    scanf("%d",&n);
    if(n <= 0){
        printf("0\n");
        exit(0);
    }
    char* text = (char*)malloc(sizeof(char)*(n+1));
    scanf("%s",text);
    text[n] = '\0';
    //do preprocessing
    long long int* hash_table = (long long int*)malloc(sizeof(long long int)*(n+1));
    long long int* pow_table = (long long int*)malloc(sizeof(long long int)*(n+1));
    
    fill_hash_table(text,hash_table,pow_table);
    scanf("%d",&number_of_queries);
    for(i = 0; i < number_of_queries; i++){
        scanf("%d",&division);
        int result = find_longest_prefix(hash_table, pow_table, division, n);
        printf("%d\n",result);
    }
    free(pow_table);
    free(hash_table);
    free(text);
    return 0;
}