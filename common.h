// common.h
#ifndef __COMMON_H__
#define __COMMON_H__
#include <stdlib.h>
#include <ext/hash_map>
#include <vector>
#include <utility>

/**
 * @brief       Generate unrepeated rand number between 0 and max-1, notice that this function is thread-unsafe.
 * @param[in]   number max
 * @return      
 *              The unrepeated number if succeeded, otherwise -1
 **/
int unrepeated_rand(int max)
{
    typedef __gnu_cxx::hash_map<int, std::vector<int>*>  array_hash_map;
    static array_hash_map* inited_array_map = new array_hash_map(5);

    array_hash_map::iterator it = inited_array_map->find(max);
    if (it != inited_array_map->end()) {
        std::vector<int>* arr = it->second;
        if (arr->empty())
            return -1;

        std::swap(arr->at(rand()%arr->size()), arr->back());
        int num = arr->back();
        arr->pop_back();
        return num;
    } else {
        std::vector<int>* arr = new std::vector<int>(max);
        for (int i = 0; i < max; ++i) 
            (*arr)[i] = i;
        inited_array_map->insert(std::make_pair(max, arr));
        return unrepeated_rand(max);
    }
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

#endif
