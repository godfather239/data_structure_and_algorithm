// bit_operation.cpp
#include <stdio.h>
#include <stdlib.h>

int calc_nonzero_bit_cnt(unsigned int num);
int test_calc_nonzero_bit_cnt()
{
    for (int i = 0; i < 10; ++i) {
        printf("num:%d, nonzero_bit_cnt:%d\n", i, calc_nonzero_bit_cnt(i));
    }
    return 0;
}

int calc_nonzero_bit_cnt(unsigned int num)
{
    if (0 == num)
        return 0;
    int cnt = 0;
    while (num) {
        num &= (num - 1);
        ++cnt;
    }
    return cnt;
}

int main(int argc, char* argv[])
{
    test_calc_nonzero_bit_cnt();
    return 0;
}
