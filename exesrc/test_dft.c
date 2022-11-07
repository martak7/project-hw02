#include <unistd.h>
#include <cmplx.h>
#include <io.h>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#define PI 3.14159
typedef float cmplx_t[2];

int main (void) {
    //signal sin(2*pi*50*t)
    //fs = 200Hz, Ts = 5ms, T=20ms
    double t, amp = 0;
    cmplx_t input[200], output[200];
    for(int i = 0; i < 200; i++){
        amp = sin(2*PI*50*i/200);
        input[i][0] =  amp;
        input[i][1] = 0;
        //t +=5;
    }
    int N = 200;
    for(int i = 0; i < N; i++) {
        printf("%f %f\n ", input[i][0], input[i][1]);
    }
    printf("\n");
    cmplx_dft(input, output, N);
    for(int i = 0; i < N; i++) {
        printf("%f %f\n ", output[i][0], output[i][1]);
    }
    int fd = open("dft.bin", O_RDWR | O_APPEND | O_CREAT, 00700);
    for(int i = 0; i < N; i++) {
        for (int k = 0; k < 2; k++) {
            float vrijednost = output[i][k];
            void *a = (void *) &vrijednost;
            int vrijednost_ieee = *((int *) a);
            write_word(fd, vrijednost_ieee);
        }
        
    }
    close(fd);
    return 0;
}
