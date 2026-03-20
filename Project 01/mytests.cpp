//==============================================================
// mytests.cpp
// Authors: Jin Seok Youn, Namu Lee Kim, Tren Meckel
// Date: 10/14/2024
// 
// Description:
// This file contains the test cases of various sorting algorithms 
// and runtime tests.
//==============================================================

#include "sorting.hpp"
#include <iostream>
#include <cstdlib>      
#include <algorithm> 
#include <chrono>    

using namespace std; 

//TestResult - a struct containing the count of passed and failed tests.
struct TestResult {
    int passed;
    int failed;
};

template <typename T>
bool isSorted(T *arr, long n);

TestResult runInsertionSortTests();
TestResult runMergeSortTests();
TestResult runQuickSortTests();
TestResult runImprovedQuickSortTests();
TestResult runRandomQuickSortTests();

template <typename Function>
bool testSortIntegers(Function sortFunction);

template <typename Function>
bool testSortDoubles(Function sortFunction);

template <typename Function>
bool testSortEmpty(Function sortFunction);

template <typename Function>
bool testSortAlreadySorted(Function sortFunction);

template <typename Function>
bool testSortReverseOrder(Function sortFunction);

template <typename Function>
bool testSortArrayLength2(Function sortFunction);

template <typename Function, typename T>
double measureTime(Function sortFunction, T* arr, long n) ;

template <typename T>
void generateRandomArray(T *arr, long n);

void testRuntimeOfSortingAlgorithms(bool isRandom);

//==============================================================
// bool testSortIntegers(Function sortFunction)
// Tests a generic sorting function with an array of integers.
// It sorts the array and checks if it is sorted.
// PARAMETERS:
// - sortFunction: a function that sorts an array of integers.
// RETURN VALUE:
// - true if the test passes (the array is sorted), false otherwise
//==============================================================
template <typename Function>
bool testSortIntegers(Function sortFunction) {
    int arr[] = {10, 7, 8, 9, 1, 5};
    long n = sizeof(arr) / sizeof(arr[0]);
    sortFunction(arr, n);
    return isSorted(arr, n);
}

//==============================================================
// bool testSortDoubles(Function sortFunction)
// Tests a generic sorting function with an array of doubles.
// It sorts the array and checks if it is sorted.
// PARAMETERS:
// - sortFunction: a function that sorts an array of doubles.
// RETURN VALUE:
// - true if the test passes (the array is sorted), false otherwise
//==============================================================
template <typename Function>
bool testSortDoubles(Function sortFunction) {
    double arr[] = {3.14, 2.71, 1.41, 1.73, 0.58};
    long n = sizeof(arr) / sizeof(arr[0]);
    sortFunction(arr, n);
    return isSorted(arr, n);
}

//==============================================================
// bool testSortEmpty(Function sortFunction)
// Tests a generic sorting function with an empty array.
// It attempts to sort the array and checks if it remains sorted.
// PARAMETERS:
// - sortFunction: a function that sorts an array.
// RETURN VALUE:
// - true if the test passes (the array is sorted), false otherwise
//==============================================================
template <typename Function>
bool testSortEmpty(Function sortFunction) {
    int arr[] = {};
    long n = sizeof(arr) / sizeof(arr[0]);
    sortFunction(arr, n);
    bool result = isSorted(arr, n);
    return result;
}

//==============================================================
// bool testSortAlreadySorted(Function sortFunction)
// Tests a generic sorting function with an already sorted array of integers.
// It checks if the algorithm maintains the sorted order.
// PARAMETERS:
// - sortFunction: a function that sorts an array of integers.
// RETURN VALUE:
// - true if the test passes (the array is sorted), false otherwise
//==============================================================
template <typename Function>
bool testSortAlreadySorted(Function sortFunction) {
    int arr[] = {1, 2, 3, 4, 5, 6};
    long n = sizeof(arr) / sizeof(arr[0]);
    sortFunction(arr, n);
    bool result = isSorted(arr, n);
    return result;
}

//==============================================================
// bool testSortReverseOrder(Function sortFunction)
// Tests a generic sorting function with a reverse ordered array of integers.
// It checks if the algorithm correctly sorts the array.
// PARAMETERS:
// - sortFunction: a function that sorts an array of integers.
// RETURN VALUE:
// - true if the test passes (the array is sorted), false otherwise
//==============================================================
template <typename Function>
bool testSortReverseOrder(Function sortFunction) {
    int arr[] = {6, 5, 4, 3, 2, 1};
    long n = sizeof(arr) / sizeof(arr[0]);
    sortFunction(arr, n);
    bool result = isSorted(arr, n);
    return result;
}

//==============================================================
// bool testSortArrayLength2(Function sortFunction)
// Tests a generic sorting function with an array of length 2.
// It checks if the algorithm correctly sorts the array.
// PARAMETERS:
// - sortFunction: a function that sorts an array of integers.
// RETURN VALUE:
// - true if the test passes (the array is sorted), false otherwise
//==============================================================
template <typename Function>
bool testSortArrayLength2(Function sortFunction) {
    int arr[] = {2, 1};
    long n = sizeof(arr) / sizeof(arr[0]);
    sortFunction(arr, n);
    bool result = isSorted(arr, n);
    return result;
}

//********************************************************
//********************************************************
//*****************Runtime Test Functions*****************
//********************************************************
//********************************************************

//==============================================================
// void generateRandomArray(T *arr, long n)
// Generates an array of random integers in the range [0, 9999].
// PARAMETERS:
// - arr: pointer to the array of type T
// - n: number of elements in the array
// RETURN VALUE:
// - None
//==============================================================
template <typename T>
void generateRandomArray(T *arr, long n) {
    srand(time(0));
    for (long i = 0; i < n; i++) {
        arr[i] = rand() % 10000; // Generating random integers between 0 and 9999
    }
}

//==============================================================
// void generateReverseSortedArray(T *arr, long n)
// Generates a reverse sorted array of size n, where elements 
// are arranged in descending order to test the worst case especially for quicksort.
// PARAMETERS:
// - arr: pointer to the array of type T
// - n: number of elements in the array
// RETURN VALUE:
// - None
//==============================================================
template <typename T>
void generateReverseSortedArray(T *arr, long n) {
    int index = 0;
    for (long i = n - 1; i >= 0; i--) {
        arr[index] = i;
        index ++;
    }
}

//==============================================================
// double measureTime(Function sortFunction, T* arr, long n)
// Measures the time taken by a sorting function to sort an array.
// PARAMETERS:
// - sortFunction: the sorting function to be measured
// - arr: pointer to the array of type T
// - n: number of elements in the array
// RETURN VALUE:
// - The time taken by the sorting function in milliseconds.
//==============================================================
template <typename Function, typename T>
double measureTime(Function sortFunction, T* arr, long n) {
    //measure start time
    chrono::time_point<chrono::high_resolution_clock> start = chrono::high_resolution_clock::now();
    sortFunction(arr, n);
    //measure end time
    chrono::time_point<chrono::high_resolution_clock> end = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> diff = end - start;
    return diff.count();
}

//==============================================================
// void testRuntimeOfSortingAlgorithms(bool isRandom)
// Tests the runtime of various sorting algorithms (Quicksort, Improved Quicksort, 
// Randomized Quicksort, and C++ std::sort) on arrays of different sizes and averages
// their execution times over 5 runs. 
// PARAMETERS:
// - isRandom: boolean indicating whether to generate a random array (true) or 
//             a reverse sorted array (false) for each run.
// RETURN VALUE:
// - None
//==============================================================
void testRuntimeOfSortingAlgorithms(bool isRandom) {
    long sizes[] = {10, 100, 1000, 10000, 100000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]); 
    const int numRuns = 10; // Number of runs for each size

    for (int i = 0; i < numSizes; ++i) {
        long size = sizes[i];
        double insertionSortTotalTime = 0.0;
        double mergeSortTotalTime = 0.0;
        double quicksortTotalTime = 0.0;
        double improvedQuicksortTotalTime = 0.0;
        double randomizedQuicksortTotalTime = 0.0;
        double stdsortTotalTime = 0.0;

        for (int run = 0; run < numRuns; ++run) {
            int* arr = new int[size]; // Array for sorting
            int* tempArr = new int[size]; // To store a copy of the original array
            if (isRandom == true) {
                generateRandomArray(arr, size); // Generate random array
            } else {
                generateReverseSortedArray(arr, size); //Generate reverse order array(quick sort worst case)
            }
            // Insertion Sort
            copy(arr, arr + size, tempArr); // Sort the copy of the original array
            insertionSortTotalTime += measureTime(insertion_sort<int>, tempArr, size);
            // Merge Sort
            copy(arr, arr + size, tempArr);
            mergeSortTotalTime += measureTime(merge_sort<int>, tempArr, size);
            
            // Quicksort
            copy(arr, arr + size, tempArr);
            quicksortTotalTime += measureTime(quicksort<int>, tempArr, size);

            // Improved Quicksort
            copy(arr, arr + size, tempArr);
            improvedQuicksortTotalTime += measureTime(improved_quicksort<int>, tempArr, size);

            // Randomized Quicksort
            copy(arr, arr + size, tempArr);
            randomizedQuicksortTotalTime += measureTime(randomized_quicksort<int>, tempArr, size);

            // C++ std::sort
            copy(arr, arr + size, tempArr);
            chrono::time_point<chrono::high_resolution_clock> start = chrono::high_resolution_clock::now();
            std::sort(tempArr, tempArr + size);
            chrono::time_point<chrono::high_resolution_clock> end = chrono::high_resolution_clock::now();
            chrono::duration<double, std::milli> diff = end - start;
            stdsortTotalTime += diff.count();

            delete[] arr; // Free the original array
            delete[] tempArr; // Free the temporary array
        }

        // Calculate and print average times
        cout << "\nSize: " << size << endl;
        cout << "Insertion Sort Average: " << (insertionSortTotalTime / numRuns) << " ms" << endl;
        cout << "Merge Sort Average: " << (mergeSortTotalTime / numRuns) << " ms" << endl;
        cout << "Quicksort Average: " << (quicksortTotalTime / numRuns) << " ms" << endl;
        cout << "Improved Quicksort Average: " << (improvedQuicksortTotalTime / numRuns) << " ms" << endl;
        cout << "Randomized Quicksort Average: " << (randomizedQuicksortTotalTime / numRuns) << " ms" << endl;
        cout << "C++ Sort Average: " << (stdsortTotalTime / numRuns) << " ms" << endl;
    }
}
//==============================================================
// bool isSorted(T *arr, long n)
// Checks if the given array is sorted in non-decreasing order.
// PARAMETERS:
// - arr: pointer to the array of type T
// - n: number of elements in the array
// RETURN VALUE:
// - true if the array is sorted, false otherwise
//==============================================================
template <typename T>
bool isSorted(T *arr, long n) {
    for (long i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

//********************************************************
//********************************************************
//*****Comprehensive Test Functions for each Sort*********
//********************************************************
//********************************************************

//==============================================================
// runImprovedQuickSortTests
// Runs a series of tests to validate the functionality of 
// the improved quicksort algorithm. Each test checks different 
// scenarios such as sorting integers, doubles, an empty array, 
// an already sorted array, reverse ordered array and an array with length 2.
// PARAMETERS: 
// - none
// RETURN VALUE: 
// - TestResult: a struct containing the count of passed 
//   and failed tests.
//==============================================================
TestResult runImprovedQuickSortTests() {
    TestResult result = {0, 0}; // Initialize passed and failed counts

    if (testSortIntegers(improved_quicksort<int>)) {
        cout << "Improved Quick Sort Test for Integers Passed" << endl;
        result.passed++;
    } else {
        cout << "Improved Quick Sort Test for Integers Failed" << endl;
        result.failed++;
    }

    if (testSortDoubles(improved_quicksort<double>)) {
        cout << "Improved Quick Sort Test for Doubles Passed" << endl;
        result.passed++;
    } else {
        cout << "Improved Quick Sort Test for Doubles Failed" << endl;
        result.failed++;
    }

    if (testSortEmpty(improved_quicksort<int>)) {
        cout << "Improved Quick Sort Test for Empty Array Passed" << endl;
        result.passed++;
    } else {
        cout << "Improved Quick Sort Test for Empty Array Failed" << endl;
        result.failed++;
    }

    if (testSortAlreadySorted(improved_quicksort<int>)) {
        cout << "Improved Quick Sort Test for Already Sorted Array Passed" << endl;
        result.passed++;
    } else {
        cout << "Improved Quick Sort Test for Already Sorted Array Failed" << endl;
        result.failed++;
    }

    if (testSortReverseOrder(improved_quicksort<int>)) {
        cout << "Improved Quick Sort Test for Reverse Ordered Array Passed" << endl;
        result.passed++;
    } else {
        cout << "Improved Quick Sort Test for Reverse Ordered Array Failed" << endl;
        result.failed++;
    }
    
    if (testSortArrayLength2(improved_quicksort<int>)) {
        cout << "Improved Quick Sort Test for Length 2 Array Passed" << endl;
        result.passed++;
    } else {
        cout << "Improved Quick Sort Test for Length 2 Array Failed" << endl;
        result.failed++;
    }

    return result; 
}

//==============================================================
// runQuickSortTests
// Runs a series of tests to validate the functionality of 
// the quicksort algorithm. Each test checks different scenarios 
// such as sorting integers, doubles, an empty array, an already 
// sorted array, reverse ordered array and an array with length 2.
// PARAMETERS: 
// - none
// RETURN VALUE: 
// - TestResult: a struct containing the count of passed 
//   and failed tests.
//==============================================================
TestResult runQuickSortTests() {
    TestResult result = {0, 0}; // Initialize passed and failed counts

    if (testSortIntegers(quicksort<int>)) {
        cout << "Quick Sort Test for Integers Passed" << endl;
        result.passed++;
    } else {
        cout << "Quick Sort Test for Integers Failed" << endl;
        result.failed++;
    }

    if (testSortDoubles(quicksort<double>)) {
        cout << "Quick Sort Test for Doubles Passed" << endl;
        result.passed++;
    } else {
        cout << "Quick Sort Test for Doubles Failed" << endl;
        result.failed++;
    }

    if (testSortEmpty(quicksort<int>)) {
        cout << "Quick Sort Test for Empty Array Passed" << endl;
        result.passed++;
    } else {
        cout << "Quick Sort Test for Empty Array Failed" << endl;
        result.failed++;
    }

    if (testSortAlreadySorted(quicksort<int>)) {
        cout << "Quick Sort Test for Already Sorted Array Passed" << endl;
        result.passed++;
    } else {
        cout << "Quick Sort Test for Already Sorted Array Failed" << endl;
        result.failed++;
    }

    if (testSortReverseOrder(quicksort<int>)) {
        cout << "Quick Sort Test for Reverse Ordered Array Passed" << endl;
        result.passed++;
    } else {
        cout << "Quick Sort Test for Reverse Ordered Array Failed" << endl;
        result.failed++;
    }
    
    if (testSortArrayLength2(quicksort<int>)) {
        cout << "Quick Sort Test for length 2 Array Passed" << endl;
        result.passed++;
    } else {
        cout << "Quick Sort Test for length 2 Array Failed" << endl;
        result.failed++;
    }

    return result; 
}

//==============================================================
// runInsertionSortTests
// Runs a series of tests to validate the functionality of
// the Insertion sort algorithm. Each test checks different scenarios
// such as sorting integers, doubles, an empty array, an already
// sorted array, reverse ordered array and an array with length 2.
// PARAMETERS:
// - none
// RETURN VALUE:
// - TestResult: a struct containing the count of passed
//   and failed tests.
//==============================================================
TestResult runInsertionSortTests() {
    TestResult result = {0, 0}; // Initialize passed and failed counts
    if (testSortIntegers(insertion_sort<int>)) {
        cout << "Insertion Sort Test for Integers Passed" << endl;
        result.passed++;
    } else {
        cout << "Insertion Sort Test for Integers Failed" << endl;
        result.failed++;
    }
    if (testSortDoubles(insertion_sort<double>)) {
        cout << "Insertion Sort Test for Doubles Passed" << endl;
        result.passed++;
    } else {
        cout << "Insertion Sort Test for Doubles Failed" << endl;
        result.failed++;
    }
    if (testSortEmpty(insertion_sort<int>)) {
        cout << "Insertion Sort Test for Empty Array Passed" << endl;
        result.passed++;
    } else {
        cout << "Insertion Sort Test for Empty Array Failed" << endl;
        result.failed++;
    }
    if (testSortAlreadySorted(insertion_sort<int>)) {
        cout << "Insertion Sort Test for Already Sorted Array Passed" << endl;
        result.passed++;
    } else {
        cout << "Insertion Sort Test for Already Sorted Array Failed" << endl;
        result.failed++;
    }
    if (testSortReverseOrder(insertion_sort<int>)) {
        cout << "Insertion Sort Test for Reverse Ordered Array Passed" << endl;
        result.passed++;
    } else {
        cout << "Insertion Sort Test for Reverse Ordered Array Failed" << endl;
        result.failed++;
    }
    if (testSortArrayLength2(insertion_sort<int>)) {
        cout << "Insertion Sort Test for length 2 Array Passed" << endl;
        result.passed++;
    } else {
        cout << "Insertion Sort Test for length 2 Array Failed" << endl;
        result.failed++;
    }
    return result;
}

//==============================================================
// runMergeSortTests
// Runs a series of tests to validate the functionality of
// the Merge sort algorithm. Each test checks different scenarios
// such as sorting integers, doubles, an empty array, an already
// sorted array, reverse ordered array and an array with length 2.
// PARAMETERS:
// - none
// RETURN VALUE:
// - TestResult: a struct containing the count of passed
//   and failed tests.
//==============================================================
TestResult runMergeSortTests() {
    TestResult result = {0, 0}; // Initialize passed and failed counts
    if (testSortIntegers(merge_sort<int>)) {
        cout << "Merge Sort Test for Integers Passed" << endl;
        result.passed++;
    } else {
        cout << "Merge Sort Test for Integers Failed" << endl;
        result.failed++;
    }
    if (testSortDoubles(merge_sort<double>)) {
        cout << "Merge Sort Test for Doubles Passed" << endl;
        result.passed++;
    } else {
        cout << "Merge Sort Test for Doubles Failed" << endl;
        result.failed++;
    }
    if (testSortEmpty(merge_sort<int>)) {
        cout << "Merge Sort Test for Empty Array Passed" << endl;
        result.passed++;
    } else {
        cout << "Merge Sort Test for Empty Array Failed" << endl;
        result.failed++;
    }
    if (testSortAlreadySorted(merge_sort<int>)) {
        cout << "Merge Sort Test for Already Sorted Array Passed" << endl;
        result.passed++;
    } else {
        cout << "Merge Sort Test for Already Sorted Array Failed" << endl;
        result.failed++;
    }
    if (testSortReverseOrder(merge_sort<int>)) {
        cout << "Merge Sort Test for Reverse Ordered Array Passed" << endl;
        result.passed++;
    } else {
        cout << "Merge Sort Test for Reverse Ordered Array Failed" << endl;
        result.failed++;
    }
    if (testSortArrayLength2(merge_sort<int>)) {
        cout << "Merge Sort Test for length 2 Array Passed" << endl;
        result.passed++;
    } else {
        cout << "Merge Sort Test for length 2 Array Failed" << endl;
        result.failed++;
    }
    return result;
}

//==============================================================
// runRandomQuickSortTests
// Runs a series of tests to validate the functionality of
// the Randomized quicksort algorithm. Each test checks different scenarios
// such as sorting integers, doubles, an empty array, an already
// sorted array, reverse ordered array and an array with length 2.
// PARAMETERS:
// - none
// RETURN VALUE:
// - TestResult: a struct containing the count of passed
//   and failed tests.
//==============================================================
TestResult runRandomQuickSortTests() {
    TestResult result = {0, 0}; // Initialize passed and failed counts

    if (testSortIntegers(randomized_quicksort<int>)) {
        cout << "Randomized Quick Sort Test for Integers Passed" << endl;
        result.passed++;
    } else {
        cout << "Randomized Quick Sort Test for Integers Failed" << endl;
        result.failed++;
    }

    if (testSortDoubles(randomized_quicksort<double>)) {
        cout << "Randomized Quick Sort Test for Doubles Passed" << endl;
        result.passed++;
    } else {
        cout << "Randomized Quick Sort Test for Doubles Failed" << endl;
        result.failed++;
    }

    if (testSortEmpty(randomized_quicksort<int>)) {
        cout << "Randomized Quick Sort Test for Empty Array Passed" << endl;
        result.passed++;
    } else {
        cout << "Randomized Quick Sort Test for Empty Array Failed" << endl;
        result.failed++;
    }

    if (testSortAlreadySorted(randomized_quicksort<int>)) {
        cout << "Randomized Quick Sort Test for Already Sorted Array Passed" << endl;
        result.passed++;
    } else {
        cout << "Randomized Quick Sort Test for Already Sorted Array Failed" << endl;
        result.failed++;
    }

    if (testSortReverseOrder(randomized_quicksort<int>)) {
        cout << "Randomized Quick Sort Test for Reverse Ordered Array Passed" << endl;
        result.passed++;
    } else {
        cout << "Randomized Quick Sort Test for Reverse Ordered Array Failed" << endl;
        result.failed++;
    }

    if (testSortArrayLength2(randomized_quicksort<int>)) {
        cout << "Random Quick Sort Test for length 2 Array Passed" << endl;
        result.passed++;
    } else {
        cout << "Random Quick Sort Test for length 2 Array Failed" << endl;
        result.failed++;
    }
    return result;
}

int main() {
    //Testing Insertion Sort
    TestResult insertionsort_result = runInsertionSortTests();
    
    cout << "Insertion Sort Tests Passed: " << insertionsort_result.passed << endl;
    cout << "Insertion Sort Tests Failed: " << insertionsort_result.failed << endl;
    cout << "\n\n";
    
    //Testing Merge Sort
    TestResult mergesort_result = runMergeSortTests();
    
    cout << "Merge Sort Tests Passed: " << mergesort_result.passed << endl;
    cout << "Merge Sort Tests Failed: " << mergesort_result.failed << endl;
    cout << "\n\n";
    
    //Testing Quick Sort
    TestResult quicksort_result = runQuickSortTests();

    cout << "Quick Sort Tests Passed: " << quicksort_result.passed << endl;
    cout << "Quick Sort Tests Failed: " << quicksort_result.failed << endl;
    cout << "\n\n";
    
    //Testing Improved Quick Sort
    TestResult improved_quicksort_result = runImprovedQuickSortTests();

    cout << "Improved Quick Sort Tests Passed: " << improved_quicksort_result.passed << endl;
    cout << "Improved Quick Sort Tests Failed: " << improved_quicksort_result.failed << endl;
    cout << "\n\n";
    
    // Testing Randomized Quick Sort
    TestResult randomQuicksort_result = runRandomQuickSortTests();

    cout << "Randomized Quick Sort Tests Passed: " << randomQuicksort_result.passed << endl;
    cout << "Randomized Quick Sort Tests Failed: " << randomQuicksort_result.failed << endl;
    //testRuntime
    // cout << "\n\n\n\n";
    // cout << "Runtime Average of Random integers: " << endl;
    // testRuntimeOfSortingAlgorithms(true);
    // cout << endl << endl;
    // cout << "Runtime Average of Reversed integers: " << endl;
    // testRuntimeOfSortingAlgorithms(false);
    return 0;
}
