#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <sys/time.h>

int getrand (int min, int max)
{
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}
double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

void CountingSort(uint32_t *inarray, uint32_t *outarray, int k, int N)
{
    int helparray[k];
    for(int i = 0; i < k; i++)
        helparray[i] = 0;
        
    for(int i = 0; i < N; i++)
        helparray[inarray[i]] = helparray[inarray[i]] + 1;
    
    for (int i = 0; i < k; i++)
        helparray[i] = helparray[i] + helparray[i - 1];
    
    for(int i = N; i >= 0; i--) {
    helparray[inarray[i]] = helparray[inarray[i]] - 1;
    outarray[helparray[inarray[i]]] = inarray[i];
    }
}

int main() {
  int N;
  scanf("%d", &N);
  uint32_t *inarray = (uint32_t *)calloc(N, sizeof(uint32_t));
  uint32_t *outarray = (uint32_t *)calloc(N, sizeof(uint32_t));
  for (int i = 0; i < N; i++){ inarray[i] = getrand (0 , 100000); };
  //for (int i = 0; i < N; i++){ printf("%d\n", inarray[i]); }
  printf("\n");
  
  double Time = wtime();
  CountingSort(inarray, outarray, 100000, N);
  double Time2 = wtime();
  double Timeend = Time2 - Time;
  //for (int i = 0; i < N; i++) {
  //    printf("%d\n", outarray[i]);
  //}
  printf("%f сек\n", Timeend);
  free(inarray);
  return 0;
}
