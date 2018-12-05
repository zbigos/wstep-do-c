#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t low = 0;
    size_t high = 25000000000;
    size_t last = 0;
    while(low+1 <= high) {
        size_t mid = (low + high)/2;
        printf("trying to malloc %ld bytes ", mid);
        void* pointer = malloc(mid);
        if(pointer == NULL) {
            printf("Failed!\n");
            high = mid;
        } else {
            free(pointer);
            printf("Ok\n");
            last = mid;
            low = mid+1;
        }
    }

    printf("POSSIBLE TO MALLOC %ld\n", last);
}