//==============================================================
// sorting.cpp
// Authors: Jin Seok Youn, Namu Lee Kim, Tren Meckel
// Date: 10/14/2024
// 
// Description:
// This file contains the implementation of various sorting algorithms,
// including insertion sort, merge sort, and several variations of quicksort.
// The algorithms are designed to work with arrays of generic type T and 
// include helper functions for element manipulation and partitioning.
//==============================================================

#include <cstdlib>  // For rand and srand functions

//HELPER FUNCTION DECLARATIONS
//Helper function declarations for merge sort
template <typename T>
void merge(T *arr, long left, long mid, long right);

template <typename T>
void mergeSortHelper(T *arr, long left, long right);

//Helper function declarations for improved quick sort 
template <typename T>
long medianOfThree(T *arr, long left, long right);

template <typename T>
void improvedQuickSortHelper(T *arr, long left, long right);

template <typename T>
int improvedPivot(T *arr, long left, long right);

//Helper function declarations for quick sort 
template <typename T>
void swapping(T *arr, long i1, long i2);

template <typename T>
long pivot(T *arr, long left, long right);

template <typename T>
void quickSortHelper(T *arr, long left, long right);

// Helper function declarations for randomized quick sort 
template <typename T>
int randomizedPivot(T *arr, long left, long right);

template <typename T>
void randomizedQuickSortHelper(T *arr, long left, long right);


//***************** INSERTION SORT *****************

//==============================================================
// insertion sort
// Function to perform in-place insertion sort on an array.
// PARAMETERS: 
// - arr : pointer to the array of type T
// - n   : number of elements in the array
// RETURN VALUE: 
// - None
//==============================================================
template <typename T>
 void insertion_sort( T *arr, long n) {
   // Iterate through each element in the array starting from the second element
   for (long i = 1; i < n; ++i) {
     T key = arr[i];  // Store the current element to be inserted
     long j = i - 1; // Initialize the position of the previous element

     // Move elements that are greater than key to one position ahead of their current position
     while (j >= 0 && arr[j] > key) {
 	   arr[j + 1] = arr[j]; // Shift element to the right
 	   j--; // Move to the previous element
     }

     // Place the key element at its correct position
     arr[j + 1] = key;
     }
 }

//***************** MERGE SORT *****************
//==============================================================
// merge
// Helper function to merge two sorted subarrays of arr.
// PARAMETERS:
// - arr   : pointer to the array of type T
// - left  : starting index of the first subarray
// - mid   : ending index of the first subarray (midpoint)
// - right : ending index of the second subarray
// RETURN VALUE:
// - None
//==============================================================
template <typename T>
void merge(T *arr, long left, long mid, long right) {
    long n1 = mid - left + 1;  
    long n2 = right - mid;    

    // Create temporary arrays
    T* L = new T[n1];
    T* R = new T[n2];

    // Copy data to temporary arrays L[] and R[]
    for (long i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (long j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    long i = 0;    // Initial index of the left subarray
    long j = 0;    // Initial index of the right subarray
    long k = left; // Initial index of the merged array

    // Merge the two subarrays back into the original array arr[]
    while (i < n1 && j < n2) {
        // Compare the current elements of L[] and R[] and copy the smaller one to arr[]
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy any remaining elements of L[]
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy any remaining elements of R[]
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    // Free temporary arrays
    delete[] L;
    delete[] R;
}

//==============================================================
// mergeSortHelper
// Helper function for recursive merge sort. Divides the array
// into two halves, sorts them, and merges them.
// PARAMETERS:
// - arr   : pointer to the array of type T
// - left  : starting index for sorting
// - right : ending index for sorting
// RETURN VALUE:
// - None
//==============================================================
template <typename T>
void mergeSortHelper(T *arr, long left, long right) {
    if (left < right) {
        long mid = left + (right - left) / 2; // Find the middle point

        // Recursively sort the first and second halves
        mergeSortHelper(arr, left, mid);
        mergeSortHelper(arr, mid + 1, right);
        
        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

//==============================================================
// merge_sort
// Merge sort function to sort the entire array. Calls the
// recursive mergeSortHelper function.
// PARAMETERS:
// - arr   : pointer to the array of type T
// - n     : size of the array to be sorted
// RETURN VALUE:
// - arr   : sorted array of type T
//==============================================================
template <typename T>
T* merge_sort(T *arr, long n) {
    mergeSortHelper(arr, 0, n - 1);
    return arr;  
}


//***************** QUICK SORT *****************

//==============================================================
// swapping
// Helper function to swap two elements in the array.
// PARAMETERS: 
// - arr : pointer to the array of type T
// - i1  : index of the first element to swap
// - i2  : index of the second element to swap
// RETURN VALUE: 
// - None
//==============================================================
template <typename T>
void swapping(T *arr, long i1, long i2) {
    T temp = arr[i1]; 
    arr[i1] = arr[i2];
    arr[i2] = temp;
}

//==============================================================
// pivot
// Helper function to partition the array and find the pivot index.
// PARAMETERS: 
// - arr   : pointer to the array of type T
// - left  : starting index for the partitioning
// - right : ending index for the partitioning
// RETURN VALUE: 
// - the index of the pivot element after partitioning
//==============================================================
template <typename T>
long pivot(T *arr, long left, long right) {
    long swap_index = left;
    T pivot = arr[left]; //Pick pivot
    for (long i = left + 1; i <= right; i++) {
        if (arr[i] < pivot) {  //swap if the value is less than pivot
            swap_index++;
            swapping(arr, swap_index, i);
        }
    }
    swapping(arr, swap_index, left);
    return swap_index;
}

//==============================================================
// quickSortHelper
// Helper function to perform the recursive quicksort algorithm.
// PARAMETERS: 
// - arr   : pointer to the array of type T
// - left  : starting index for sorting
// - right : ending index for sorting
// RETURN VALUE: 
// - None
//==============================================================
template <typename T>
void quickSortHelper(T *arr, long left, long right) {
    if (left >= right) { 
        return;
    }

    long pivotnum = pivot(arr, left, right);
    quickSortHelper(arr, left, pivotnum - 1);  
    quickSortHelper(arr, pivotnum + 1, right); 
}

//==============================================================
// quicksort
// Main function to perform quicksort on the given array.
// PARAMETERS: 
// - arr : pointer to the array of type T
// - n   : the number of elements in the array
// RETURN VALUE: 
// - None
//==============================================================
template <typename T>
void quicksort(T *arr, long n) {
    quickSortHelper(arr, 0, n - 1); 
}

//***************** Improved QUICK SORT *****************
//==============================================================
// long medianOfThree(T *arr, long left, long right)
// Selects the median of three elements in the array to use as the pivot.
// The three elements are the leftmost, middle, rightmost positions. 
// Sorts these elements and returns the index of the median.
// PARAMETERS:
// - arr  : pointer to the array of type T
// - left : starting index of the array segment
// - right: ending index of the array segment
// RETURN VALUE:
// - the index of the median element of the three selected elements
//==============================================================
template <typename T>
long medianOfThree(T *arr, long left, long right) {
    long middle = left + (right - left) / 2;

    if (arr[left] > arr[middle]) {
        swapping(arr, left, middle);
    }
    if (arr[left] > arr[right]) {
        swapping(arr, left, right);
    }
    if (arr[middle] > arr[right]) {
        swapping(arr, middle, right);
    }

    // Return the index of the median element
    return middle;
}

//==============================================================
// int improvedPivot(T *arr, long left, long right)
// Selects an improved pivot using the median of five strategy 
// and partitions the array around this pivot.
// PARAMETERS:
// - arr   : pointer to the array of type T
// - left  : starting index for partitioning
// - right : ending index for partitioning
// RETURN VALUE:
// - the index of the pivot element after partitioning
//==============================================================
template <typename T>
int improvedPivot(T *arr, long left, long right) {
    long pivotIndex = medianOfThree(arr, left, right); //pick pivot with median
    swapping(arr, pivotIndex, left);  
    long swapIndex = left;

    for (long i = left + 1; i <= right; i++) {
        if (arr[i] < arr[left]) {
            swapIndex++;
            swapping(arr, swapIndex, i);
        }
    }
    swapping(arr, swapIndex, left);  
    return swapIndex;
}

//==============================================================
// void improvedQuickSortHelper(T *arr, long left, long right)
// Helper function for the improved quicksort algorithm. Recursively 
// sorts the left and right halves of the array using the improved pivot 
// selection strategy.
// PARAMETERS:
// - arr   : pointer to the array of type T
// - left  : starting index for sorting
// - right : ending index for sorting
// RETURN VALUE:
// - None
//==============================================================
template <typename T>
void improvedQuickSortHelper(T *arr, long left, long right) {
    if (left >= right) {
        return;
    }

    long pivotIndex = improvedPivot(arr, left, right);
    improvedQuickSortHelper(arr, left, pivotIndex - 1);
    improvedQuickSortHelper(arr, pivotIndex + 1, right);
}

//==============================================================
// void improvedQuicksort(T *arr, long n)
// Main function to perform the improved quicksort algorithm.
// Uses the improved pivot selection strategy. For arrays with fewer
// than 5 elements, it falls back to the standard quicksort algorithm.
// PARAMETERS:
// - arr : pointer to the array of type T
// - n   : the number of elements in the array
// RETURN VALUE:
// - None
//==============================================================
template <typename T>
void improved_quicksort(T *arr, long n) {
    if (n < 3) {
        //Since we use 3 mid points for median selection, 
        //If the array length is less than 3, we can use regular quicksort.
        quickSortHelper(arr, 0, n - 1); 
    }
    improvedQuickSortHelper(arr, 0, n - 1);
}

// ***************** RANDOMIZED QUICK SORT *****************

//==============================================================
// randomizedPivot
// Helper function to select a random pivot and partition the array.
// PARAMETERS:
// - arr   : pointer to the array of type T
// - left  : starting index for the partitioning
// - right : ending index for the partitioning
// RETURN VALUE:
// - the index of the pivot element after partitioning
//==============================================================

template <typename T>
int randomizedPivot(T *arr, long left, long right) {
    // Choose a random pivot index between left and right
    long randomIndex = left + rand() % (right - left + 1);
    
    // Swap the randomly chosen pivot with the leftmost element
    swapping(arr, left, randomIndex);

    // Call the standard pivot function to partition
    return pivot(arr, left, right);
}

//==============================================================
// randomizedQuickSortHelper
// Helper function for recursive randomized quicksort.
// PARAMETERS:
// - arr   : pointer to the array of type T
// - left  : starting index for sorting
// - right : ending index for sorting
// RETURN VALUE:
// - None
//==============================================================
template <typename T>
void randomizedQuickSortHelper(T *arr, long left, long right) {
    if (left >= right) {
        return; // Base case: stop recursion if subarray is one element or empty
    }

    long pivotnum = randomizedPivot(arr, left, right);  // Get random pivot index
    randomizedQuickSortHelper(arr, left, pivotnum - 1); // Recursively sort left side
    randomizedQuickSortHelper(arr, pivotnum + 1, right); // Recursively sort right side
}

//==============================================================
// randomized_quicksort
// Main function to perform randomized quicksort on the given array.
// PARAMETERS:
// - arr : pointer to the array of type T
// - n   : the number of elements in the array
// RETURN VALUE:
// - None
//==============================================================
template <typename T>
void randomized_quicksort(T *arr, long n) {
    randomizedQuickSortHelper(arr, 0, n - 1); // Call helper function to sort the entire array
}
