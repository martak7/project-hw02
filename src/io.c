#include <unistd.h>

int read_word(int fd){
    int word;
    read(fd, &word, sizeof(int));
    return word;
}

short read_half(int fd){
    short halfword;
    read(fd, &halfword, sizeof(short));
    return halfword;
}

void write_word(int fd, int word) {
    write(fd, &word, sizeof(int));
}

void write_half(int fd, short word){
    write(fd, &word, sizeof(short));
}