// Sorting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "8Sorts.h"

#define RANGE 10000000
#define NUMBER 5000

int comp(int *a, int *b) {
    return *b - *a;
}

template<typename Algorithm, class T, typename Comp>
void test(Algorithm func, T *start, T *answer, int size, Comp comp, const char *name) {
    T *test = new T[size];
    memcpy(test, start, size * sizeof(T));
    clock_t begin = clock();
    func(test, test + size, comp);
    clock_t end = clock();
    for (int i = 0; i < NUMBER; i++)
        if (answer[i] != test[i]) {
            printf("%s wrong at %d\n", name, i);
            return;
        }
    printf("%s correct using %d ms\n", name, end - begin);
}

using namespace Sine::Sorting;

int main()
{
    int *unsorted = new int[NUMBER];
    srand(time(NULL));
    for (int i = 0; i < NUMBER; i++) {
        unsorted[i] = (((rand() / 2) << 15) | rand()) % RANGE;
        //printf("%d ", unsorted[i]);
    }
    printf("\n");
    printf("generated %d unsorted integer from 0 to %d\n", NUMBER, RANGE - 1);

    int *sorted = new int[NUMBER];
    memcpy(sorted, unsorted, NUMBER * sizeof(int));
    std::sort(sorted, sorted + NUMBER);

    //test(InsertionSort<int, int(int *, int *)>, unsorted, sorted, NUMBER, comp, "InsertionSort");
    test(ShellSort<int, int(int *, int *)>, unsorted, sorted, NUMBER, comp, "ShellSort");
    //test(SelectionSort<int, int(int *, int *)>, unsorted, sorted, NUMBER, comp, "SelectionSort");
    //test(BubbleSort<int, int(int *, int *)>, unsorted, sorted, NUMBER, comp, "BubbleSort");
    test(MergeSort<int, int(int *, int *)>, unsorted, sorted, NUMBER, comp, "MergeSort");
    test(QuickSort<int, int(int *, int *)>, unsorted, sorted, NUMBER, comp, "QuickSort");
    test(HeapSort<int, int(int *, int *)>, unsorted, sorted, NUMBER, comp, "HeapSort");

    delete[] sorted;
    delete[] unsorted;
    system("pause");
    return 0;
}
