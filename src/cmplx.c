#include <stdio.h>
#include <math.h>

#define PI 3.14159

typedef float cmplx_t[2];

void cmplx_div(cmplx_t a, cmplx_t b, cmplx_t c) {
    float num_real = a[0]*b[0] + a[1]*b[1];
    float num_imag = a[1]*b[0] - a[0]*b[1];
    float denum =  powf(b[0], 2) + powf(b[1], 2);
    c[0] = num_real/denum;
    c[1] = num_imag/denum;
}

void cmplx_mul(cmplx_t a, cmplx_t b, cmplx_t c){
    c[0] = a[0]*b[0] - a[1]*b[1];
    c[1] = a[0]*b[1] + a[1]*b[0];
}

double cmplx_mag(cmplx_t a){
    return sqrt(pow(a[0], 2) + pow(a[1], 2));
}

double cmplx_phs(cmplx_t a){
    return atan(a[1]/a[0]);
}

double cmplx_real(double mag, double phs){
    return mag * cos(phs);
}

double cmplx_imag(double mag, double phs){
    return mag * sin(phs);
}

void cmplx_dft(cmplx_t *input, cmplx_t *output, int N){
    for (int k = 0; k < N; k++) {
        cmplx_t b, c, sum;
        sum[0] = 0;
        sum[1] = 0;
        for (int n = 0; n < N-1; n++) {
            b[0] = cos(2*PI*k*n/N);
            b[1] = -sin(2*PI*k*n/N);
            cmplx_mul(input[n], b, c);
            sum[0] = sum[0] + c[0];
            sum[1] = sum[1] + c[1];
        }
        output[k][0] = sum[0];
        output[k][1] = sum[1]; 
    }
}
void cmplx_idft(cmplx_t *input, cmplx_t *output, int N){
    for(int k = 0; k < N; k++) {
        cmplx_t b, c, sum;
        sum[0] = 0;
        sum[1] = 0;
        for (int n = 0; n < N; n++) {
            b[0] = cos(2*PI*k*n/N);
            b[1] = sin(2*PI*k*n/N);
            cmplx_mul(input[n], b, c);
            sum[0] = sum[0] + c[0];
            sum[1] = sum[1] + c[1];
        }
        output[k][0] = sum[0] / N;
        output[k][1] = sum[1] / N;
    }
}