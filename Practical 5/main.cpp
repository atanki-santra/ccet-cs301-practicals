#include <iostream>
#include <iomanip>
#include <time.h>
#include <Windows.h>
#include <chrono>
#include "sort.h"

using namespace std;
using namespace std::chrono;

int main()
{
    system("CLS");
    size_t SIZE{1};
    int *array{nullptr};
    cout << "Initializing Array..." << endl;
    createNumbers();
    system("CLS");
    cout << "RESULTS: " << endl
         << endl;
    int i = 10;
    void (*fptr[5])(int *, size_t) = {bubbleSort, insertionSort, selectionSort, shellSort, radixsort};
    void (*functPtr)(int *, size_t);
    cout << string(110, '-') << endl
         << " | " << setw(15) << left << "Size of Array"
         << " | " << setw(15) << left << "Bubble Sort"
         << " | " << setw(15) << left << "Insertion Sort"
         << " | " << setw(15) << left << "Selection Sort"
         << " | " << setw(15) << left << "Shell Sort"
         << " | " << setw(15) << left << "Radix Sort"
         << " | " << endl
         << string(110, '-') << endl;
    while (SIZE <= MAX_SIZE)
    {
        cout << " | " << setw(15) << right << SIZE << " | ";
        for (size_t i{0}; i < 5; i++)
        {
            array = initialiseArray(SIZE);
            functPtr = fptr[i];
            auto start = high_resolution_clock::now();
            functPtr(array, SIZE);
            auto end = high_resolution_clock::now();
            duration<double, std::milli> timeTaken = end - start;
            deleteArray(array);
        }
        SIZE *= 2;
        cout << endl;
    }
    cout << string(110, '-') << endl;
    return 0;
}
