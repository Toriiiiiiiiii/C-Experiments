#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void msort_iter(int* buf, size_t nmem) {
	if(nmem == 1) return;

	int *left = malloc((nmem+1) / 2 * sizeof(int));
	int *right = malloc(nmem / 2 * sizeof(int));

	memcpy(left, buf, (nmem+1) / 2 * sizeof(int));
	memcpy(right, buf+(nmem+1)/2, nmem / 2 * sizeof(int));

	msort_iter(left, (nmem+1) / 2);
	msort_iter(right, nmem / 2);

	int i = 0, j = 0;
	int bufIndex = 0;
	while(i < (nmem+1) / 2 && j < nmem / 2) {
		int a = left[i];
		int b = right[j];

		if(a < b) {
			buf[bufIndex] = a;
			i++;
		} else if(a > b) {
			buf[bufIndex] = b;
			j++;
		} else {
			buf[bufIndex] = a;
			buf[bufIndex+1] = b;
			i++;
			j++;
			bufIndex++;
		}

		bufIndex++;
	}

	while(i < (nmem+1) / 2) {
		buf[bufIndex] = left[i];
		i++;
		bufIndex++;
	}

	while(j < nmem / 2) {
		buf[bufIndex] = right[j];
		j++;
		bufIndex++;
	}

	free(left);
	free(right);
}

void msort(int* src, int* buf, size_t nmem) {
	memcpy(buf, src, nmem * sizeof(int));
	msort_iter(buf, nmem);
}

int main(int argc, char** argv) {
	int unsorted[10] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	int sorted[10]   = { 0 };

	printf("C Experiment #1 :: Merge Sort\n");
	msort(unsorted, sorted, 10);

	printf("Unsorted Array\n");
	printf("--------------\n");
	for(int i = 0; i < 10; ++i) {
		printf("%d\n", unsorted[i]);
	}

	printf("Sorted Array\n");
	printf("------------\n");
	for(int i = 0; i < 10; ++i) {
		printf("%d\n", sorted[i]);
	}
}
