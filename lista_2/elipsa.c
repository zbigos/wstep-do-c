#include <stdio.h>

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    
    for(int i = -a; i< a; i++) {
        for(int j = -b; j< b; j++)
            printf("%c", (double)(((double)i+0.5)*((double)i+0.5))/(double)(a*a) + (double)(((double)j+0.5)*((double)j+0.5))/(double)(b*b) <= 1.0 ?'#':' ');

            printf("\n");
        }
    
}