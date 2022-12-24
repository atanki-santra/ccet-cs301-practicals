#ifndef SORT_H
#define SORT_H

#include <iostream>
#include <fstream>
#define MAX_SIZE 20000000
using namespace std;

void createNumbers();
int* initialiseArray(size_t SIZE);
void deleteArray(int* arr);
void swap(int &a, int &b);
void printArray(int *arr, size_t SIZE);

void bubbleSort(int *arr, size_t SIZE);
void insertionSort(int *arr, size_t SIZE);
void selectionSort(int *arr, size_t SIZE);
void shellSort(int *arr, size_t SIZE);
void radixsort(int *arr, size_t SIZE);

#endif //SORT_H