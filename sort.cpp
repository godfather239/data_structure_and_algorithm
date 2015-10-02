// sort.cpp
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <utility>

typedef int (*sort_func_ptr) (int*, int);

int partition(int* a, int p, int r);
int test_partition();
int print_array(int* a, int n);
int quicksort(int* a, int n);
int test_sort(int n, sort_func_ptr sf);


// The simpliest partition implementaion which chooses arr[r] as pivot by default
int partition(int* a, int p, int r)
{
    while (p < r) {
        while ((p < r) && (a[p] <= a[r]))
            ++p;
        if (p < r)
            std::swap(a[p], a[r--]);
        while ((p < r) && (a[p] <= a[r]))
            --r;
        if (p < r)
            std::swap(a[p++], a[r]);
    }
    return p;
}

int test_partition()
{
    int a[10] = {1, 5, 7, 6, 5, 10, 8, 3, 4, 6};
    printf("Before partition:\n");
    print_array(a, 10);
    int q = partition(a, 0, 9);
    printf("After partition: q = %d\n", q);
    print_array(a, 10);
    return 0;
}

int print_array(int* a, int n)
{
    if (!a || n <= 0) {
        return -1;
    }
    for (int i = 0; i < n; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}

int quicksort(int* a, int n)
{
    if (!a || n <= 0)
        return -1;
    int pivot = partition(a, 0, n - 1);
    quicksort(a, pivot);
    quicksort(a + pivot + 1, n - pivot - 1);
    return 0;
}

int test_sort(int n, sort_func_ptr sf)
{
    if (n <= 0 || !sf)
        return -1;

    const int NUM_MAX = 100;
    int* a = new int[n];
    for (int i = 0; i < n; ++i) {
        a[i] = rand() % NUM_MAX;
    }
    printf("Before sort:\n");
    print_array(a, n);
    (*sf)(a, n);
    printf("After sort: \n");
    print_array(a, n);

    return 0;
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        fprintf(stderr, "USAGE: ./sort <array_size>\n");
        return -1;
    }

    srand(time(NULL));
    test_sort(atoi(argv[1]), quicksort);

    //test_partition();
    return 0;
}

