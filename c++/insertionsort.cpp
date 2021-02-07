/*
 ORDINA ELEMENTI NEL RANGE [start, end)
da: https://gist.github.com/svdamani/dc57e4d1b00342d4507d
 */

#ifndef INSERTIONSORT
#define INSERTIONSORT
#include <algorithm>

template <class Iterator>
void insertionsort(Iterator begin, Iterator end) {
    std::iter_swap(begin, std::min_element(begin, end));
    for (Iterator b = begin; ++b < end; begin = b)
        for (Iterator c = b; *c < *begin; --c, --begin)
            std::iter_swap(begin, c);
}

#endif

