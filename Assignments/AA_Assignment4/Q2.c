#include<stdio.h>
#include<stdlib.h>
#define DEBUG 1
#define Q 1000000007
long long int get_inverse(long long int, long long int);
long long int euclid_extended(long long int, long long int , long long int*, long long int*);
int main(){
    int N;
    scanf("%d",&N);
    int* remainders = (int*)malloc(N*sizeof(int));
    int* divisors = (int*)malloc(N*sizeof(int));
    long long int divisor_product = 1;
    long long int b;
    long long int b_inverse;
    long long int b_prime;
    long long int ans = 0;
    long long int product;
    int i;
    for(i = 0; i < N; i++){
        scanf("%d %d", divisors+i, remainders+i);
        divisor_product = ((divisor_product%Q)*(divisors[i]%Q))%Q;
    }
    if(DEBUG){
        printf("divisor_product = %llu\n",divisor_product);
        printf("divisor product pairs\n");
        for(i = 0; i < N; i++){
            printf("%d %d\n",divisors[i], remainders[i]);
        }
    }
    
    for(i = 0; i < N; i++){
        b = divisor_product/divisors[i];
        b_inverse = get_inverse(b, divisors[i]);
        b_prime = b_inverse%divisors[i];
        if(DEBUG){
            printf("b = %llu, b_prime = %llu\n", b, b_prime);
        }
        product = ((remainders[i]%Q)*(b%Q)*(b_prime%Q))%Q;
        if(DEBUG)
            printf("\nproduct = %llu \n", product);
        ans = ((ans) + (product));
    }
    if(DEBUG){
        printf("\nans = %llu",ans%Q);
    }
    printf("%lld\n",(ans%divisor_product)%Q);
    free(remainders);
    free(divisors);
    return 0;
}

long long int get_inverse(long long int b, long long int m){
    long long int x;
    long long int y;
    long long int gcd = euclid_extended(b , m, &x, &y);
    if(gcd != 1){
        return -1;
    }
    return (x%m + m)%m;
}

long long int euclid_extended
    (long long int a, long long int b,
     long long int* x, long long int* y){
    if(a == 0){
        *x = 0;
        *y = 1;
        return b;
    }
    long long int x_copy;
    long long int y_copy;
    long long int gcd_recur = euclid_extended(b%a, a, &x_copy, &y_copy);
    *x = y_copy - (b/a)*x_copy;
    *y = x_copy;
    return gcd_recur;

}