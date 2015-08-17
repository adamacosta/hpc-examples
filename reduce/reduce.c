#include <stdio.h>
#include <stdint.h>
#include <omp.h>
#include <time.h>

#define LEN 5 * (1 << 20)
#define N_TRIALS 1000

int main(int argc, char **argv) {
	uint8_t arr[LEN];
	int sum, i, j;
	clock_t start, stop;

	/* Initialize the array to sum */
	for (i = 0; i < LEN; i++)
		arr[i] = 1;

	printf("sequential,parallel\n");
	for (j = 0; j < N_TRIALS; j++) {

		start = clock();
		sum = 0;
		for (i = 0; i < LEN; i++)
			sum += arr[i];
		stop = clock();
		printf("%f,", (double)(stop - start) / CLOCKS_PER_SEC);

		start = clock();
		sum = 0;
		#pragma omp parallel for reduction(+:sum)
		for (i = 0; i < LEN; i++) {
			sum += arr[i];
		}
		stop = clock();
		printf("%f\n", (double)(stop - start) / CLOCKS_PER_SEC);

	}

	return 0;
}