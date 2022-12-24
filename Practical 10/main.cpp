/*Problem 10: Binary Heap Tree: Write a modular program to construct Binary Heap tree for the following
data set.
*/

#include <iostream>
#include <cmath>
#define DATASET_SIZE 18
using namespace std;

void swap(int &a, int &b)
{
    a = a + b;
    b = a - b;
    a = a - b;
}

int *upArray(int *array, size_t size)
{
    int *temp = new int[size * 2];
    for (size_t i{0}; i < size; i++)
        temp[i] = array[i];
    delete[] array;
    return temp;
}

int *downArray(int *array, size_t size)
{
    int *temp = new int[size / 2];
    for (size_t i{0}; i < size; i++)
        temp[i] = array[i];
    delete[] array;
    return temp;
}

struct maxHeap
{
    int *array{nullptr};
    size_t size{0};
    void insert(int value)
    {
        if (ceil(log2(size)) == floor(log2(size)))
            array = upArray(array, size);
        size = size + 1;
        int index = size;
        array[index - 1] = value;
        int parent;
        while (index > 1)
        {
            parent = index / 2;

            if (array[parent - 1] < array[index - 1])
            {
                swap(array[parent - 1], array[index - 1]);
                index = parent;
            }
            else
                return;
        }
    }
    void print()
    {
        for (size_t i{0}; i < size; i++)
            cout << array[i] << " ";
    }
    void clear()
    {
        delete[] array;
        size = 0;
    }
};

struct minHeap
{
    int *array{nullptr};
    size_t size{0};
    void insert(int value)
    {
        if (ceil(log2(size)) == floor(log2(size)))
            array = upArray(array, size);
        size = size + 1;
        int index = size;
        array[index - 1] = value;
        int parent;
        while (index > 1)
        {
            parent = index / 2;

            if (array[parent - 1] > array[index - 1])
            {
                swap(array[parent - 1], array[index - 1]);
                index = parent;
            }
            else
                return;
        }
    }
    void print()
    {
        for (size_t i{0}; i < size; i++)
            cout << array[i] << " ";
    }
    void clear()
    {
        delete[] array;
        size = 0;
    }
};

void maxHeapify(int* array, int n, int i)
{
    int largest = i;
    int left = 2*i;
    int right = 2*i +1;
    
    if(left < n && array[largest-1] < array[left-1])
    {
        largest = left;
    }
    if(right < n && array[largest-1] < array[right-1])
    {
        largest = right;
    }

    if(largest != i)
    {
        swap(array[largest-1], array[i-1]);
        maxHeapify(array, n , largest);
    }
}

void minHeapify(int* array, int n, int i)
{
    int smallest = i;
    int left = 2*i;
    int right = 2*i +1;
    
    if(left < n && array[smallest-1] > array[left-1])
    {
        smallest = left;
    }
    if(right < n && array[smallest-1] > array[right-1])
    {
        smallest = right;
    }
    
    if(smallest != i)
    {
        swap(array[smallest-1], array[i-1]);
        minHeapify(array, n , smallest);
    }
}

void showMaxHeap()
{
    int* dataSet = new int[DATASET_SIZE]{97, 88, 95, 66, 55, 95, 48, 60, 45, 48, 55, 62, 77, 25 , 38, 18, 40, 38};
    maxHeap* heap = new maxHeap();
    for (size_t i{0}; i < DATASET_SIZE; i++)
    {
        heap->insert(dataSet[i]);
        cout << "Inserted : " << dataSet[i] << endl;
    }
    cout<<string(60,'-')<<endl;
    cout << "GENERATED MAX HEAP (INSERTING EACH VALUE ONE BY ONE): " << endl;
    heap->print();
    heap->clear();
    cout << endl <<"GENERATED MAX HEAP (USING HEAPIFY): " << endl;
    for(int i = DATASET_SIZE/2; i > 0; i--)
        maxHeapify(dataSet, DATASET_SIZE + 1, i);
    for(size_t i{0}; i < DATASET_SIZE; i++)
        cout<<dataSet[i]<<" ";
    cout<<endl;
    delete []dataSet;
}

void showMinHeap()
{
    int* dataSet = new int[DATASET_SIZE]{97, 88, 95, 66, 55, 95, 48, 60, 45, 48, 55, 62, 77, 25 , 38, 18, 40, 38};
    minHeap* heap = new minHeap();
    for (size_t i{0}; i < DATASET_SIZE; i++)
    {
        heap->insert(dataSet[i]);
        cout << "Inserted : " << dataSet[i] << endl;
    }
    cout<<string(60,'-')<<endl;
    cout << "GENERATED MIN HEAP (INSERTING EACH VALUE ONE BY ONE): " << endl;
    heap->print();
    heap->clear();
    cout << endl <<"GENERATED MIN HEAP (USING HEAPIFY): " << endl;
    for(int i = DATASET_SIZE/2 ; i > 0; i--)
        minHeapify(dataSet, DATASET_SIZE + 1, i);
    for(size_t i{0}; i < DATASET_SIZE; i++)
        cout<<dataSet[i]<<" ";
    cout<< endl;
    delete []dataSet;
}

int main()
{
    cout<<string(60,'-')<<endl;
    showMaxHeap();
    cout<<string(60,'-')<<endl;
    showMinHeap();
    cout<<string(60,'-')<<endl;
    return 0;
}