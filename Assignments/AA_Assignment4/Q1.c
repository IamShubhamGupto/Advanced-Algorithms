#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<complex.h>
#define DEBUG 1
#define PI 3.1415926535897932384

struct cmplx{
    double real_;
    double imag_;
};
typedef struct cmplx complex_t;

void bit_reverse_copy(complex_t*, complex_t*);
void do_fft(complex_t*, complex_t*, int, int);
void multiply_polynomials(complex_t*, complex_t*, int);
complex_t multiply_complexes(complex_t, complex_t);
complex_t add_complexes(complex_t, complex_t);
complex_t subtract_complexes(complex_t, complex_t);

int main(){
    int degree_bound;
    int i,j;
    scanf("%d",&degree_bound);
    complex_t* a_coeff = (complex_t*)malloc(sizeof(complex_t)*degree_bound);
    complex_t* b_coeff = (complex_t*)malloc(sizeof(complex_t)*degree_bound);
    complex_t* c_coeff = (complex_t*)malloc(sizeof(complex_t)*2*degree_bound);
    for(i = 0; i < degree_bound; i++){
        scanf("%d",a_coeff+i);
        c_coeff[i] = 0;
    }
    j = i;
    for(i = 0; i < degree_bound; i++){
        scanf("%d",b_coeff+i);
        c_coeff[j+i] = 0;
    }
    //fast_fourier_transform(a_coeff, b_coeff, c_coeff, degree_bound);
    for(i = 0; i < 2*degree_bound; i++){
        printf("%d ",c_coeff[i]);
    }
    printf("\n");
    free(a_coeff);
    free(b_coeff);
    free(c_coeff);
    return 0;
}

void bit_reverse_copy(complex_t* a, complex_t* rev_a_copy){
    a = 0;
}

void do_fft(complex_t* a, complex_t* y, int n, int inv){
    complex_t w;
    w.real_ = 1.0;
    w.imag_ = 0.0;
    complex_t w_n;
    complex_t twiddle_factor;
    complex_t* a_0 = (complex_t*)malloc(sizeof(complex_t)*(n/2));
    complex_t* a_1 = (complex_t*)malloc(sizeof(complex_t)*(n/2));
    complex_t* y_0 = (complex_t*)malloc(sizeof(complex_t)*(n/2));
    complex_t* y_1 = (complex_t*)malloc(sizeof(complex_t)*(n/2));
    int i,k;
    if(n == 1){
        if(DEBUG){
            printf("Base case found !!\n");
        }
        y[0] = a[0];
        return;
    }
    if(inv){
        w_n.real_ = cos(-2*PI/(double)n);;
        w_n.imag_ = sin(-2*PI/(double)n);
    }else{
        w_n.real_ = cos(2*PI/(double)n);
        w_n.imag_ = sin(2*PI/(double)n); 
    }
    for(i = 0; i < (n/2); i++){
        a_0[i] = a[2*i];
        a_1[i] = a[(2*i) +1];
    }
    do_fft(a_0,y_0,n/2,inv);
    do_fft(a_1,y_1,n/2,inv);
    for(i = 0; i < n/2; i++){
        twiddle_factor = multiply_complexes(w, y_1[i]);
        y[i] = add_complexes(y_0[i], twiddle_factor);
        y[i+ (n/2) = subtract_complexes(y_0[i], twiddle_factor);
    }
    w = multiply_complexes(w, w_n);
    free(a_0);
    free(a_1);
    free(y_0);
    free(y_1);

}

void multiply_polynomials(complex_t* a, complex_t* b, int n){
    complex_t* y_a = (complex_t*)malloc(sizeof(complex_t)*n);
    complex_t* y_b = (complex_t*)malloc(sizeof(complex_t)*n);
    int i,j;
    do_fft(a, y_a, n, 0);
    do_fft(b, y_b, n, 0);
    for(i = 0; i < n; i++){
        y_a[i] = multiply_complexes(y_a[i],y_b[i]);
    }
    do_fft(y_a,a,n,1);
    for(i = 0; i < n-1; i++){
        a[i].real_ /= n;
    }
    free(y_a);
    free(y_b);

}

complex_t multiply_complexes(const complex_t a, const complex_t b){
    complex_t product;
    product.real_ = (a.real_*b.real_) - (a.imag_*b.imag_);
    product.imag_ = (a.real_*b.imag_) - (a.imag_*b.real_);
    return product;
}

complex_t add_complexes(const complex_t a, const complex_t b){
    complex_t sum;
    sum.real_ = a.real_ + b.real_;
    sum.imag_ = a.imag_ + b.imag_;
    return sum;
}

complex_t subtract_complexes(complex_t, complex_t){
    complex_t diff;
    diff.real_ = a.real_ - b.real_;
    diff.imag_ = a.imag_ - b.imag_;
    return diff;
}

