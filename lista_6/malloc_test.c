#include <stdio.h>
#include <stdlib.h>

int main() {
    long long int low = 0;
    long long int high = 25000000000;

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
            low = mid+1;
        }
    }

    printf("POSSIBLE TO MALLOC %lld\n", (low+high)/2);
}