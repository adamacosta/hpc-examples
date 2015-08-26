#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SWAP(x,y) do {     \
	typeof(x) _x = x;      \
	typeof(y) _y = y;      \
	x = _y;                \
	y = _x;                \
} while(0)

void print_arr(int arr[], int start, int stop) {
	int i;

	for (i = start; i < stop + 1; i++)
		printf("%d ", arr[i]);

	printf("\n");
}

int partition(int arr[], int start, int stop) {
	int i, j;

	int idx = start + rand() % (stop - start + 1);
	int pivot = arr[idx];
	SWAP(arr[idx], arr[stop]);

	i = start;
	for (j = start; j < stop; j++) {
		if (arr[j] <= pivot) {
			SWAP(arr[i], arr[j]);
			i++;
		} 
	}
	SWAP(arr[i], arr[stop]);

	return i;
}

void quicksort(int arr[], int start, int stop) {
	if (start < stop) {
		// partition and recurse
		int idx = partition(arr, start, stop);
		quicksort(arr, start, idx - 1);
		quicksort(arr, idx + 1, stop);
	}
}

void parquicksort(int arr[], int start, int stop) {
	if (start < stop) {
		// partition and recurse
		int idx = partition(arr, start, stop);
		if (stop - start < 10000) {
			quicksort(arr, start, idx - 1);
			quicksort(arr, idx + 1, stop);
		} else {
			#pragma omp parallel sections
			{
				#pragma omp section
				parquicksort(arr, start, idx - 1);
				#pragma omp section
				parquicksort(arr, idx + 1, stop);
			}
		}
	}
}

void test_run(int MAX_LEN) {
	int i, next_num;
	int *nums = calloc(MAX_LEN, sizeof(int));
	int *parnums = calloc(MAX_LEN, sizeof(int));
	double start, stop;

	for (i = 0; i < MAX_LEN; i++) {
		next_num = rand() % MAX_LEN;
		nums[i] = next_num;
		parnums[i] = next_num;
	}

	start = omp_get_wtime();
	quicksort(nums, 0, MAX_LEN - 1);
	stop = omp_get_wtime();
	printf("%d,%f,", MAX_LEN, stop - start);

	start = omp_get_wtime();
	parquicksort(nums, 0, MAX_LEN - 1);
	stop = omp_get_wtime();
	printf("%f\n", stop - start);

	free(nums);
	free(parnums);
}

int main() {
	int i;
	printf("elements,sequential,parallel\n");
	for (i = 10; i <= 24; i++) {
		test_run(1 << i);
	}

	return 0;
}