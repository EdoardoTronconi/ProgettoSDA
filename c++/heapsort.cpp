/*
 ORDINA ELEMENTI NEL RANGE [start, end)
 */

#ifndef HEAPSORT
#define HEAPSORT

#include <algorithm>

template <typename Iterator>
void heapsort (Iterator start, Iterator end){
    std::make_heap(start, end);
    std::sort_heap(start, end);
}



#endif
