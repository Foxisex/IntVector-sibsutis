#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <inttypes.h>

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

void InsertionSort(uint32_t *array, int N)
{
    int key, j;
    
    for(int i = 2; i <= N; i++) {
        key = array[i];
        j = i - 1;
        while(j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}

/*void inssort(uint32_t array[], int N) {

  for(int i = 1; i < N; i++) 
  {
	int k = i;
	while (k > 0 && array[k-1] > array[k])
	 {
	  int temp = array[k-1];
	  array[k-1] = array[k];
	  array[k] = temp;
	  k -= 1;
         }
  }
for (int i = 0; i < N; i++){ printf("%d\n", array[i]); }
}*/

int main() {
  int N;
  scanf("%d", &N);
  uint32_t * array = (uint32_t*) calloc (N, sizeof(uint32_t));
  for (int i = 0; i < N; i++){ array [i] = getrand (0, 100000);}
  
  printf("\n");\
  double Time = wtime();
  InsertionSort(array, N);
  double Time2 = wtime();
  double Timeend = Time2 - Time;
  //for (int i = 0; i < N; i++){ printf("%d\n", array[i]); }
  printf("%f сек\n", Timeend);
  return 0;
}
