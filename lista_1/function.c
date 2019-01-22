#include <stdio.h>
#include "math.h"

int min(int a, int b) {
    return a>b?b:a;
}

double mind(double a, double b) {
    return a>b?b:a;
}

int foo(int n, int m) {
    for(int i = 2; i < min(n,m); i++) {
        for(int j = 2; j < i; j++)
            if(i%j == 0)
                break;
        if(n%i != m%i)
            return i;
    }
}

int main() {
    double best = 0;
    int w,q;
    for(int i = 3; i <= 1000; i++)
        for(int j = i+1; j <= 1000; j++) {
            double res = foo(i,j)/log((double)j);
            if(res > best) {
                best = res;
                w = i;
                q = j;
            }
        }

    printf("n = %d m = %d wynik = %lf", q, w, best);
}