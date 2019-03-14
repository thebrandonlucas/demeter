#include <stdio.h>
#include <string.h>

int partition(A, p, r) {
	int pivot = A[r]; 
	int i = p - 1; 
	for (int j = p; j < r - 1; j++) {
		if (A[j] <= pivot) {
			i++; 
			swap(A[i], A[j]); 
		}
	}
	swap(A[i + 1], A[r]); 
	return pivot; 
}

void quicksort(A, p, r) {
	if (p < r) {
		int q = partition(A, p, r); 
		quicksort(A, p, q - 1); 
		quicksort(A, q + 1, r); 
	}
}

int main() {
	int arrayLength = 0; int temp = 0; 
	printf("Enter array length: "); 
	scanf("%d", arrayLength); 

	int inArray[arrayLength]; 

	printf("Enter array for quicksort: ");
	for (int i = 0; i < arrayLength; i++) {
		scanf("%d", &array[i]); 
	}

	return 0; 
}