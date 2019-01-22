#include <stdio.h>

#define ITERATION_NUM 50000

int main() {
    double result = 0;
    for(int i = 0 ; i < ITERATION_NUM; i++)
        result += (double)(1-2*(i%2))/((double)(1+2*i)*(double)(1+2*i));

    printf("%.10lf", result);
}