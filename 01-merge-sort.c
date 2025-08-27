#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Recursive function to perform merge sort
void msort_iter(int* buf, size_t nmem) {
	// Base case: If only 1 element, break out
	if(nmem == 1) return;

	// Split the array into 2 smaller arrays
	int *left = malloc((nmem+1) / 2 * sizeof(int));
	int *right = malloc(nmem / 2 * sizeof(int));

	memcpy(left, buf, (nmem+1) / 2 * sizeof(int));
	memcpy(right, buf+(nmem+1)/2, nmem / 2 * sizeof(int));

	// Perform merge sort on the 2 new arrays
	msort_iter(left, (nmem+1) / 2);
	msort_iter(right, nmem / 2);

	// Insert values into the result in order
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

	// If 'right' was emptied first, add the rest of 'left'
	while(i < (nmem+1) / 2) {
		buf[bufIndex] = left[i];
		i++;
		bufIndex++;
	}

	// If 'left' was emptied first, add the rest of 'right'
	while(j < nmem / 2) {
		buf[bufIndex] = right[j];
		j++;
		bufIndex++;
	}

	// Don't forget to free() what you malloc()!
	free(left);
	free(right);
}

// Wrapper function to sort array
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
