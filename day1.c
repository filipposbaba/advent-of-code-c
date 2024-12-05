#include <stdio.h>
#include <stdlib.h>

const int ARRAY_SIZE = 1000;

// Implementation of a merge sort
void mergeSort(int* array, int size) {
    // Base case
    if (size == 1) return;

    // Until the base case is hit, continue creating sub-arrays
    int half = size / 2;
    int otherHalf = size - half;
    int* leftArray = (int*) malloc(sizeof(int) * half);
    int* rightArray = (int*) malloc(sizeof(int) * otherHalf);
    // Populate the arrays
    for (int i = 0; i < half; i++) {
        leftArray[i] = array[i];
    }
    for (int i = 0; i < otherHalf; i++) {
        rightArray[i] = array[half + i];
    }
    mergeSort(leftArray, half);
    mergeSort(rightArray, otherHalf);

    // Once sub-arrays hit base case (or return), reassemble sorted list
    int i = 0;          // Index of main array
    int j1 = 0, j2 = 0;     // Indexes of sub-arrays
    // Loop until the end of one of the sub-arrays
    while (j1 < half && j2 < otherHalf) {
        if (leftArray[j1] <= rightArray[j2]) {
            array[i] = leftArray[j1];
            j1++;
        } else {
            array[i] = rightArray[j2];
            j2++;
        }
        i++;
    }

    // Populate the rest of 'array' with remaining values
    while (j1 < half) {
        array[i] = leftArray[j1];
        j1++;
        i++;
    }
    while (j2 < otherHalf) {
        array[i] = rightArray[j2];
        j2++;
        i++;
    }

    free(leftArray);
    free(rightArray);
    return;
}

long calculateSortedArrayDistance(int* sortedArray1, int* sortedArray2, int size) {
    long total = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (sortedArray1[i] >= sortedArray2[i]) total += sortedArray1[i] - sortedArray2[i];
        else total += sortedArray2[i] - sortedArray1[i];
    }

    return total;
}

long calculateSimilarityScore(int* sortedArray1, int* sortedArray2, int size) {
    // Calculation relies on both arrays being sorted - as it progresses
    // through the first array and compares its values to those of the  
    // second array, it progressively truncates the second array to exclude 
    // values smaller than the ith value in the first array
    long similarity = 0;
    int i = 0, j = 0;
    int instances = 0;
    while (i < ARRAY_SIZE && j < ARRAY_SIZE) {
        if (sortedArray1[i] > sortedArray2[j]) {
            j++;
        } else if (sortedArray1[i] == sortedArray2[j]) {
            instances += 1;
            j++;
        } else {
            // If instances != 0, then that means previous values matched - in that case,
            // once they have stopped matching (since, by this point, sortedArray1[i] < sortedArray2[j]),
            // calculate the similarity, and reset 'instances'
            if (instances != 0) {
                similarity += instances * sortedArray1[i];
                instances = 0;
            }
            i++;
        } 
    }

    return similarity;
}

int main(int n, char *args[n]) {
    if (n != 2) {
        printf("Please pass in a single file as an argument!\n");
        return -1;
    }

    FILE *inputFile = fopen((char*) args[1], "r");
    if (inputFile == NULL) {
        printf("Error: File invalid, or not found!\n");
        return -1;
    }

    int fileArray1[ARRAY_SIZE], fileArray2[ARRAY_SIZE];
    int index = 0;
    int temp1, temp2; // Not strictly neccessary, but more readable this way

    // While end of the file hasn't been reached
    while (!feof(inputFile)) {
        // If able to read two int values from the file (which are stored in the temp variables)..
        if (fscanf(inputFile, "%d   %d", &temp1, &temp2) == 2) {
            fileArray1[index] = temp1;
            fileArray2[index] = temp2;
            index += 1;
            // ..store in our arrays, and increase the index
        }
    }

    mergeSort(fileArray1, ARRAY_SIZE);
    mergeSort(fileArray2, ARRAY_SIZE);

    long distance = calculateSortedArrayDistance(fileArray1, fileArray2, ARRAY_SIZE);
    printf("The distance between these two arrays is: %ld\n", distance);
    long similarity = calculateSimilarityScore(fileArray1, fileArray2, ARRAY_SIZE);
    printf("The similarity score of these two arrays is: %ld\n", similarity);

    return 0;
}
