// unrepeated_rand.h
#ifndef __unrepeated_rand_h__
#define __unrepeated_rand_h__
#include <stdlib.h>
#include <vector>
#include <utility>

class UnrepeatedRand
{
public:
    explicit UnrepeatedRand(int max) : m_max(max)
    {init(); }
    int next()
    {
        if (!m_arr.empty()) {
            std::swap(m_arr[rand()%m_arr.size()], m_arr.back());
            int num = m_arr.back();
            m_arr.pop_back();
            return num;
        } else {
            return -1;
        }
    }
    void reset()
    {
        m_arr.clear();
        init();
    }
private:
    void init()
    {
        if (m_max > 0) {
            m_arr.reserve(m_max);
            for (int i = 0; i < m_max; ++i)
                m_arr.push_back(i);
        }
    }
    int m_max;
    std::vector<int> m_arr;
};

#endif
