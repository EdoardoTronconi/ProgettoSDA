/*
 ORDINA ELEMENTI NEL RANGE [start, end)
 da: https://gist.github.com/svdamani/dc57e4d1b00342d4507d
 */

#ifndef MERGESORT
#define MERGESORT
#include<algorithm>

template <class Iterator>
inline void mergesort(Iterator begin, Iterator end) {
    if (end <= begin + 1) return;
    Iterator middle = begin + (end - begin) / 2;
    mergesort(begin, middle);
    mergesort(middle, end);
    std::inplace_merge(begin, middle, end);
}



#endif
