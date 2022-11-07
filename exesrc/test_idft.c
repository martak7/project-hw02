#include <unistd.h>
#include <cmplx.h>
#include <io.h>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>

#define PI 3.14159
typedef float cmplx_t[2];

int main (void) {
    //signal sin(2*pi*50*t) -> DFT 
    //fs = 200Hz, Ts = 5ms, T=20ms

    cmplx_t input[200], output[200];
    int N = 200;

    int fd = open("dft.bin", O_RDWR, 00700);
    
    for(int i = 0; i < N; i++) {
        for (int k = 0; k < 2; k++) {
            int vrijednost_ieee = read_word(fd);
            void *a = (void *) &vrijednost_ieee;
            float vrijednost = *((float *) a);
            input[i][k] = vrijednost;
        }
    }
    for(int i = 0; i < N; i++) {
        printf("%f %f\n ", input[i][0], input[i][1]);
    }
    printf("\n");
    cmplx_idft(input, output, N);
    for(int i = 0; i < N; i++) {
        printf("%f %f\n ", output[i][0], output[i][1]);
    }
    close(fd);
    return 0;
}
