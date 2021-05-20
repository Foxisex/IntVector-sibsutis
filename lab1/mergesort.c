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

void Merge(uint32_t *array, unsigned int low, unsigned int mid, unsigned int high)
{
	uint32_t help_array[high];
	for(int i = low; i <= high; i++)
		help_array[i] = array[i];

	unsigned int l = low;
	unsigned int r = mid + 1;
	unsigned int i = low;

	while(l <= mid && r<=high) {
		if(help_array[l] <= help_array[r]){
			array[i] = help_array[l];
			l++;
		}
		else {
			array[i] = help_array[r];
			r++;
		}
		i++;
	}

	while(l <= mid) {
		array[i] = help_array[l];
		l++;
		i++;
	}
	while(r <= high) {
		array[i] = help_array[r];
		r++;
		i++;
	}
}

void MergeSort(uint32_t *array,unsigned int low,unsigned int high)
{
	if(low < high){
		unsigned int mid = (low + high) / 2;
		MergeSort(array, low, mid);
		MergeSort(array, mid + 1, high);
		Merge(array, low, mid, high);
	}
}

int main() {
	 
  int N;
  scanf("%d", &N);
  uint32_t *array = (uint32_t*)malloc(sizeof(uint32_t) * N);
  for (int i = 0; i < N; i++){ array[i] = getrand (0, 100000);}
  //for (int i = 0; i < N; i++){ printf("%d\n", array[i]); }
  printf("\n");\

  double Time = wtime();
  MergeSort(array, 0, N);
  double Time2 = wtime();
  double Timeend = Time2 - Time;
  
  

  //for (int i = 0; i < N; i++){ printf("%d\n", array[i]);}
  printf("%f сек\n", Timeend);
  return 0;
}