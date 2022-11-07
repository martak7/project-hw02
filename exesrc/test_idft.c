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

    cmplx_t input[8], output[8];
    int N = 8;

    int fd = open("dft.bin", O_RDWR);
    
    for(int i = 0; i < sizeof(output); i++) {
        for (int k = 0; k < 2; k++) {
            int vrijednost_ieee = read_word(fd);
            void *a = (void *) &vrijednost_ieee;
            float vrijednost = *((float *) a);
            input[i][k] = vrijednost;
        }
    }
    cmplx_idft(input, output, N);
    for(int i = 0; i < N; i++) {
        printf("%f %f\n ", output[i][0], output[i][1]);
    }
    close(fd);
    return 0;
}
