#include "sort.h"

void createNumbers()
{
    ofstream fout("numbers.txt");
    srand(time(NULL));
    for (size_t i = 0; i < MAX_SIZE; i++)
        fout << rand() << ' ';   
    fout.close();
}

int *initialiseArray(size_t SIZE)
{
    int *arr = new int[SIZE];
    ifstream fin("numbers.txt");
    for (size_t i{0}; i < SIZE; i++)
        fin >> arr[i];
    fin.close();
    return arr;
}

void deleteArray(int *arr)
{
    delete[] arr;
}

void swap(int &a, int &b)
{
    a = a + b;
    b = a - b;
    a = a - b;
}

void printArray(int *arr, size_t SIZE)
{
    for (size_t i{0}; i < SIZE; i++)
        cout << arr[i] << ' ';
    cout << endl
         << endl;
}

void bubbleSort(int *arr, size_t SIZE)
{
    for (size_t i{0}; i < SIZE - 1; i++)
    {
        for (size_t j{0}; j < SIZE - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}

void insertionSort(int *arr, size_t SIZE)
{
    int i, key, j;
    for (i = 1; i < SIZE; i++)
    {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(int *arr, size_t SIZE)
{
    size_t i, j, min_index;
    for (i = 0; i < SIZE - 1; i++)
    {
        min_index = i;
        for (j = i + 1; j < SIZE; j++)
        {
            if (arr[j] < arr[min_index])
                min_index = j;
        }
        if (min_index != i)
            swap(arr[min_index], arr[i]);
    }
}

void shellSort(int *arr, size_t SIZE)
{
    for (int gap = SIZE / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < SIZE; i += 1)
        {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
}

int getMax(int *arr, size_t SIZE)
{
    int max = arr[0];
    for (int i = 1; i < SIZE; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

void countSort(int *arr, size_t SIZE, int exp)
{
    int *output = new int[SIZE];
    int i, count[10] = {0};

    for (i = 0; i < SIZE; i++)
        count[(arr[i] / exp) % 10]++;

    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (i = SIZE - 1; i >= 0; i--)
    {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (i = 0; i < SIZE; i++)
        arr[i] = output[i];
}

void radixsort(int *arr, size_t SIZE)
{
    int max = getMax(arr, SIZE);

    for (int exp = 1; max / exp > 0; exp *= 10)
        countSort(arr, SIZE, exp);
}