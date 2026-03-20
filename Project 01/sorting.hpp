//==============================================================
// sorting.hpp
// Authors: Jin Seok Youn, Namu Lee Kim, Tren Meckel
// Date: 10/14/2024
// 
// Description:
// This header file declares various sorting algorithms, including
// insertion sort, merge sort, and several variations of quicksort.
// These algorithms are implemented as templates to operate on 
// arrays of generic type T.
//==============================================================
#include <iostream>
using namespace std;

#ifndef SORTING_HPP
#define SORTING_HPP

template <typename T>
void insertion_sort(T *arr, long n);

template <typename T>
T* merge_sort(T *arr, long n);

template <typename T>
void quicksort(T *arr, long n);

template <typename T>
void improved_quicksort(T *arr, long n);

template <typename T>
void randomized_quicksort(T *arr, long n);

#endif

#include "sorting.cpp"
