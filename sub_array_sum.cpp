// sub_array_sum.cpp
#include <stdio.h>

#define max(a,b) (((a) > (b)) ? (a) : (b))

// division algorithm
// from <<Programming pearls>> chapter 8
// NOTICE: maxsum for negative number is 0.
int maxsum_div(int* arr, int size)
{
    if (!arr || size <= 0)
        return -1;
    if (1 == size)
        return arr[0] > 0 ? arr[0] : 0;

    int m = (size - 1) / 2;
    int maxsum_left = 0;
    int sum = 0;
    for (int i = m; i >= 0; --i) {
        sum += arr[i];
        maxsum_left = max(sum, maxsum_left);
    }
    int maxsum_right = 0;
    sum = 0;
    for (int i = m + 1; i < size; ++i) {
        sum += arr[i];
        maxsum_right = max(sum, maxsum_right);
    }

    int ls = maxsum_div(arr, m + 1);
    int rs = maxsum_div(arr + m + 1, size - m - 1);
    if (ls > rs)
        return ls > (maxsum_left + maxsum_right) ? ls : (maxsum_left + maxsum_right);
    else
        return rs > (maxsum_left + maxsum_right) ? rs : (maxsum_left + maxsum_right);
}

int maxsum_by_scan(int* arr, int size)
{
    if (!arr || size <= 0)
        return -1;
    int maxsum = 0;
    int maxsofar = 0;
    for (int i = 0; i < size; ++i) {
        maxsofar = max(maxsofar + arr[i], 0);
        maxsum = max(maxsum, maxsofar);
    }
    return maxsum;
}

void test()
{
    int a[10] = {31,-41,59,26,-53,58,97,-93,-23,84};
    //printf("maxsum is: %d\n", maxsum_div(a, 10));
    printf("maxsum is: %d\n", maxsum_by_scan(a, 10));
}

int main(int argc, char* argv[])
{
    test();
    return 0;
}
