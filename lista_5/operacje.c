#include <stdio.h>

int its_time_to_stop = 0;

int numbers[100];
char ops[100];

void recursion(int place, int value, int end) {
    if (its_time_to_stop)
        return;

    if(place == end) {
        if(value == 1) {
            for(int i = 0 ; i <= end; i++)
                printf("%d %c ",numbers[i], ops[i]);
            its_time_to_stop = 1;
        }

        return;
    }

    ops[place] = '|';
        recursion(place+1, value | numbers[place+1], end);
    ops[place] = '&';
        recursion(place+1, value & numbers[place+1], end);
    ops[place] = '<';
        recursion(place+1, value << numbers[place+1], end);
    ops[place] = '>';
        recursion(place+1, value >> numbers[place+1], end);
    ops[place] = '^';
        recursion(place+1, value ^ numbers[place+1], end);

    return;
}

int main() {
    int n;
    scanf("%d", &n);
    for(int i = 0 ; i < n; i++)
        scanf("%d", &numbers[i]);
    recursion(0, numbers[0], n-1);

    if(its_time_to_stop == 0)
        printf("No solutions");
}