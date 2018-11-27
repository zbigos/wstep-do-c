#include <stdio.h>
#include <string.h>

#define FILL(pointer, number, bytes)    \
    do {                                \
        char payload = 0;                   \
        for(int i = 1 ; i <= number*8; i++) {\
            payload = payload | (#bytes[i%strlen(#bytes)]=='1'?((1<<((8-i%8)-1))):0); \
            if(i % 8 == 0 && i > 0) {   \
                *((char*)pointer+((i-1)/8)) = payload; \
                payload = 0;            \
            }                           \
        }                               \
    } while(0)

int main() {
    char t[10];
    FILL(t,10,01);
    printf("%.10s\n",t); // UUUUUUUUUU
    FILL(t,10,0110000101100010);
    printf("%.10s",t); // ababababab
}