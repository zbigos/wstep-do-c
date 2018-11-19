#include <stdio.h>

int awaiting = -5;
int longest = 0;
int current = 0;

int max(int a, int b) {
  return a>b?a:b;
}

void counter(int bit) {
  if(bit > 0)
    bit = 1;

  if(awaiting == -5) { // this is just for initialization
    current = 1;
    awaiting = 1 - bit;
  }

  if(awaiting == bit) {
    awaiting = 1 - awaiting;
    current++;
  } else {
    longest = max(longest, current);
    current = 1;
    awaiting = 1-bit;
  }
}

int main() {
  while(1) {
    int a = getchar();
    if(a == EOF || a == '\n')
      break;

    for(int i = 7 ; i >= 0; i--)
      counter(a & (1<<i));
  }

  printf("%d", max(longest, current));
}
