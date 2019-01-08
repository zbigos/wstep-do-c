#include <stdio.h>
#include <stdlib.h>

char a[20] = "rucham dzieci";

struct ArrayQueue {
    int *t;
    size_t size; // Liczba elementów w kolejsce
    size_t first; // Indeks pierwszego elementu w kolejce
    size_t capacity; // Wielkość tablicy
};


struct ArrayQueue make_queue(size_t initial_capacity) {
    struct ArrayQueue Q;
    Q.capacity = initial_capacity;
    Q.first = -1;
    Q.t = (int*)malloc(initial_capacity * sizeof(int));
    return Q;
}

int pop_first(struct ArrayQueue *q) {
    if(q->size >= 1) {
        q->size --;
        int ret = q->t[q->first];
        q->first = (q->first+1)%(q->capacity);
        return ret;
    } else {
        return -1;
    }
}

void push_last(struct ArrayQueue *q, int value) {
    if (q->size+1 > q->capacity) {
        int new_size = 1;
        while(new_size <= q->capacity)
            new_size *= 2;
        
        int *newtab = (int*)malloc(new_size*sizeof(int));
        int iter = 0;
        int help = q->size;
        while(q->size > 0) {
            newtab[iter] = pop_first(q);
            iter++;
        }

        free(q->t);
        q->t = newtab;
        q->capacity = new_size;
        q->size = help;
        q->first = 0;
    }

    q->t[(q->first+q->size)%q->capacity] = value;
    q->size++;
}

void peek(struct ArrayQueue *p) {
    printf("\n{");
    for(int i = 0 ; i < p->capacity; i++)
        printf("%d ", p->t[i]);
    printf("}\n");
}

int main() {
    struct ArrayQueue q = make_queue(1);
    for (int i = 0; i < 4; i++) 
        push_last(&q, i);
        
    printf("%lu %lu %lu,", q.size, q.first, q.capacity);
    //peek(&q);
    for (int i = 0; i < 7; i++) {
        printf(" %i", pop_first(&q));
        push_last(&q, i);
    }
    //peek(&q);
    push_last(&q, 0);
    //peek(&q);
    printf(", %i, %lu %lu %lu", pop_first(&q), q.size, q.first, q.capacity);

}
