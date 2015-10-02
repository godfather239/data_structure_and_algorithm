// sort.cpp
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <utility>

typedef int (*sort_func_ptr) (int*, int);

#define heap_left(p) (2 * (p) + 1)
#define heap_right(p) (2 * ((p) + 1))

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

/**
 * @breif       Keep feature of max heap
 * @param[in]   heap array pointer
 * @param[in]   array size
 * @param[in]   array index of the sub tree which should be reshaped to keep feature of max heap
 * @return
 *              0       succeed
 *              -1      error happens
 **/
int max_heapify(int* a, int size, int p);

//int heap_left(int p);
//int heap_right(int p);

/**
 * @brief       Build max heap on array specified by argv[@a]
 * @param[in]   pointer of array
 * @param[in]   array size
 * @return
 *              0       succeed
 *              -1      failed
 **/
int build_max_heap(int* a, int size);

int heap_sort(int* a, int size);

int test_heap_build(int size);

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

int max_heapify(int* a, int size, int p)
{
    assert(a && size > 0 && p >= 0 && p < size);
    int target = p;
    int l = heap_left(p);
    int r = heap_right(p);
    if (l < size && a[l] > a[target])
        target = l;
    if (r < size && a[r] > a[target])
        target = r;
    if (p != target) {
        std::swap(a[p], a[target]);
        return max_heapify(a, size, target);
    } else {
        return 0;
    }
}

//int heap_left(int p)
//{
//    return 2 * p + 1;
//}
//
//int heap_right(int p)
//{
//    return 2 * (p + 1);
//}

/**
 * Do max_heapify operation from the leaf nodes to root nodes level by level,
 * then we will get a well builded max heap.
 **/
int build_max_heap(int* a, int size)
{
    if (!a || size <= 0)
        return -1;
    for (int i = size / 2 - 1; i >= 0; --i)
        max_heapify(a, size, i);
    return 0;
}

int heap_sort(int* a, int size)
{
    if (!a || size <= 0)
        return -1;
    build_max_heap(a, size);
    while (size > 1) {
        std::swap(a[0], a[size-1]);
        max_heapify(a, --size, 0);
    }
    return 0;
}

int test_heap_build(int size)
{
    if (size <= 0)
        return -1;
    int* a = new int[size];
    for (int i = 0; i < size; ++i)
        a[i] = rand() % 100;

    printf("Before build heap:\n");
    print_array(a, size);
    build_max_heap(a, size);
    printf("After build heap: \n");
    print_array(a, size);

    delete[] a;
    return 0;
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        fprintf(stderr, "USAGE: ./sort <array_size>\n");
        return -1;
    }

    srand(time(NULL));
    for (int i = 0; i < 10; ++i) {
        printf("Test %d: \n", i+1);
        test_sort(atoi(argv[1]), heap_sort);
    }
    //test_select();
    //int a[10] = {1, 15, 7, 6, 5, 10, 8, 3, 4, 9};
    //print_kmin(a, 10, 5);
    //test_heap_build(atoi(argv[1]));

    //test_partition();
    return 0;
}

