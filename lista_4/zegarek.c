#include <stdio.h>
#include <math.h>
#define CLOCK_DIAM 15
#define bool int
#define true 1
#define false 0

double max(double a, double b) {
  return a<b?b:a;
}

double min(double a, double b) {
  return a>b?b:a;
}

double flabs(double a) {
  return a>0?a:-a;
}

bool eps_dist(double a, double b, double eps) {
  double ln = min(a,b);
  double bn = max(a,b);
  if(flabs(bn-(ln+360.0)) < eps) return true;
  return (bn-ln < eps)?true:false;
}

int atan2_fixd(double a, double b) {
  return (int)(720+90+atan2(a,b)*180.0/M_PI)%360;
}

int main() {
  int godzina, minuta;
  scanf("%d %d", &godzina, &minuta);
  double hang = 360*(double)(godzina % 12)/12.0;
  double mang = 360*(double)minuta/60.0;

  for(int i = -CLOCK_DIAM; i < CLOCK_DIAM; i++) {
    for(int j = -CLOCK_DIAM; j < CLOCK_DIAM; j++)
      if ((i * i + j * j) < (CLOCK_DIAM * CLOCK_DIAM))
        if(eps_dist(atan2_fixd((double)i,(double)j), hang, (double)(CLOCK_DIAM*CLOCK_DIAM)/(double)(i*i+j*j)))
          printf("#");
        else if(eps_dist(atan2_fixd((double)i,(double)j), mang, (double)(CLOCK_DIAM*CLOCK_DIAM)/(double)(i*i+j*j)))
          printf("x");
        else printf(".");
      else
        printf(" ");
      printf("\n");
    }
}
