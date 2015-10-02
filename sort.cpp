// sort.cpp
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <utility>

typedef int (*sort_func_ptr) (int*, int);

int partition(int* a, int p, int r);
int random_partition(int* a, int p, int r);
int test_partition();
int print_array(int* a, int n);
int quicksort(int* a, int n);
int test_sort(int n, sort_func_ptr sf);

/**
 * @brief       Select the k-th number in array by ascending order. Notice that the function
 *              will change order of array elements.
 * @param[in]   array pointer
 * @param[in]   array length
 * @param[in]   the k-th number index, k is in range:[1,n]
 * @return
 *              index of the k-th number, -1 if error happens
 **/
int select_asc(int* a, int n, int k);
int print_kmin(int* a, int n, int k);


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

// Enhance stability of partition.
int random_partition(int* a, int p, int r)
{
    std::swap(a[(rand()%(r-p+1))+p], a[r]);
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
    //int pivot = partition(a, 0, n - 1);
    int pivot = random_partition(a, 0, n - 1);
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

    delete[] a;
    return 0;
}

int select_asc(int* a, int n, int k)
{
    if (!a || n <= 0 || k <= 0 || k > n)
        return -1;
    int p = random_partition(a, 0, n - 1);
    if (p == k - 1)
        return p;
    else if (p > k - 1)
        return select_asc(a, p, k);
    else
        return p + 1 + select_asc(a + p + 1, n - p - 1, k - p - 1);
}

int test_select()
{
    int a[10] = {1, 15, 7, 6, 5, 10, 8, 3, 4, 9};
    for (int i = 1; i <= 7; ++i) {
        printf("Test %d:\n", i);
        int index = select_asc(a, 10, i);
        if (index >= 0 && index < 10)
            printf("Found the %d-th number in array, result index: %d, number: %d\n", i, index, a[index]);
        else
            printf("Error on finding the %d-th number in array, result index: %d\n", i, index);
    }
    return 0;
}

int print_kmin(int* a, int n, int k)
{
    if (!a || n <= 0 || k <= 0 || k > n)
        return -1;
    int p = select_asc(a, n, k);
    printf("The min-%d elements in array are: \n", k);
    print_array(a, p+1);
    return 0;
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        fprintf(stderr, "USAGE: ./sort <array_size>\n");
        return -1;
    }

    srand(time(NULL));
    //for (int i = 0; i < 100; ++i) {
    //    printf("Test %d: \n", i+1);
    //    test_sort(atoi(argv[1]), quicksort);
    //}
    test_select();
    int a[10] = {1, 15, 7, 6, 5, 10, 8, 3, 4, 9};
    print_kmin(a, 10, 5);

    //test_partition();
    return 0;
}

