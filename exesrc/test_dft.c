#include <unistd.h>
#include <cmplx.h>
#include <io.h>
#include <fcntl.h>
#include <math.h>
#define PI 3.14159
typedef float cmplx_t[2];

int main (void) {
    //signal sin(2*pi*50*t)
    //fs = 200Hz, Ts = 5ms, T=20ms
    double t, amp = 0;
    cmplx_t input[8], output[8];
    for(int i = 0; i < 8; i++){
        amp = sin(2*PI*50*t/1000);
        input[i][0] =  t;
        input[i][1] = amp;
        t +=5;
        
    }
    int N = 8;
    cmplx_dft(input, output, N);
    int fd = open("dft.bin", O_RDWR | O_APPEND | O_CREAT, 00700);
    for(int i = 0; i < sizeof(output); i++) {
        for (int k = 0; k < 2; k++) {
            float vrijednost = output[i][k];
            void *a = (void *) &vrijednost;
            int vrijednost_ieee = *((int *) a);
            int vrijednost_cijeli_broj = (int) vrijednost;
            write_word(fd, vrijednost_ieee);
        }
        
    }
    close(fd);
    return 0;
}
