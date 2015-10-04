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

int test_find()
{
    srand(time(NULL));
    const int MAX = 8;
    UnrepeatedRand rand(MAX);
    int arr[7] = {0};
    int mask = 4;

    for (int testtime = 1; testtime <= 10; ++testtime) {
        rand.reset();
        for (int i = 0; i < 7; ++i) {
            arr[i] = rand.next();
        }
        printf("Test time: %d, array is: \n", testtime);
        print_array(arr, 7);
        int out = 0;
        find_missing_num(arr, 7, mask, out);
        printf("Missing num: %d\n", out);
    }
    return 0;
}

int main(int argc, char* argv[])
{
    test_find();
    return 0;
}
