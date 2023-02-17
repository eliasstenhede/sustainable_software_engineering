#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 10000

static inline int is_prime(unsigned short n) {
    unsigned short i;
    for (i = 2; i < n; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    unsigned short i;
    unsigned short* buffer = malloc(BUFFER_SIZE*sizeof(short));
    unsigned short count = 0;
    for (i = 2; i <= 65000; i++) {
        if (is_prime(i)) {
            if (count >= BUFFER_SIZE) {
                fprintf(stderr, "Error: buffer overflow\n");
                return 1;
            }
            buffer[count++] = i;
        }
    }
    printf("count: %d, last prime: %d", count, buffer[count-1]);
    return 0;
}
