// search.cpp
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "unrepeated_rand.h"
#include "common.h"

using std::vector;

int find_missing_num(int* arr, int size, int mask, int& out)
{
    if (!arr || size <= 0 || mask <= 0)
        return -1;
    vector<int> lows;
    vector<int> highs;
    for (int i = 0; i < size; ++i) {
        if (arr[i] & mask) {
            highs.push_back(arr[i]);
        } else {
            lows.push_back(arr[i]);
        }
    }
    if (highs.size() >= lows.size()) {
        out &= ~mask;
        find_missing_num(!lows.empty() ? (&lows[0]) : NULL, lows.size(), mask >> 1, out);
    } else {
        out |= mask;
        find_missing_num(!highs.empty() ? (&highs[0]) : NULL, highs.size(), mask >> 1, out);
    }
    return 0;
}

// Find missing number iteratively
int find_missing_iter(int* arr, int size, int mask, int& out)
{
    if (!arr || size <= 0 || mask <= 0)
        return -1;
    int* left = arr;
    int* right = arr + size - 1;
    while ((left <= right) && (mask > 0)) {
        int* curr = left;
        int* leftend = left;
        while (curr <= right) {
            // The numbers which have 0 on mask bit will be saved at left.
            if ((*curr & mask) == 0) 
                std::swap(*curr, *leftend++);
            ++curr;
        }
        // Chose smaller segment
        if ((leftend - left) <= (right - leftend + 1)) {
            out &= ~mask;  // Set bit to 0
            right = leftend - 1;
        } else {
            out |= mask;  // Set bit to 1
            left = leftend;
        }
        mask >>= 1;
    }
    return 0;
}

// limit is 2^k
int find_missing(int* arr, int size, int limit, int& out)
{
    if (!arr || size <= 0 || limit <= 0)
        return -1;
    int mask = limit >> 1;
    int* left = arr;
    int* right = arr + size - 1;
    while ((left <= right) && (mask > 0)) {
        int* curr = left;
        int* leftend = left;
        while (curr <= right) {
            // The numbers which have 0 on mask bit will be saved at left.
            if ((*curr & mask) == 0) 
                std::swap(*curr, *leftend++);
            ++curr;
        }
        // Chose smaller segment
        if ((leftend - left) <= (right - leftend + 1)) {
            out &= ~mask;  // Set bit to 0
            right = leftend - 1;
        } else {
            out |= mask;  // Set bit to 1
            left = leftend;
        }
        mask >>= 1;
    }
    return 0;
}

int test_find()
{
    srand(time(NULL));
    /**
     * NOTICE:  MAX should be 2^k, k is in range [1, 32]; mask is 2^(k-1)
     **/
    const int MAX = 8;
    const int len = 7;
    int mask = 4;
    UnrepeatedRand rand(MAX);
    int arr[len] = {0};

    for (int testtime = 1; testtime <= 10; ++testtime) {
        rand.reset();
        for (int i = 0; i < len; ++i) {
            arr[i] = rand.next();
        }
        printf("Test time: %d, array is: \n", testtime);
        print_array(arr, len);
        int out = 0;
        //find_missing_num(arr, len, mask, out);
        //find_missing_iter(arr, len, mask, out);
        find_missing(arr, len, MAX, out);
        printf("Missing num: %d\n", out);
    }
    return 0;
}

int main(int argc, char* argv[])
{
    test_find(); 
    return 0;
}
