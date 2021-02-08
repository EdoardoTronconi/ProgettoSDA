/*
 ORDINA ELEMENTI NEL RANGE [start, end)
 */

#ifndef HEAPSORT
#define HEAPSORT

#include <algorithm>

template <typename Iterator>
void max_heapify(const Iterator start, const Iterator end, Iterator i){
    Iterator leftChild = std::next(start, 2*(std::distance(start, i) + 1) - 1);
    Iterator rightChild = std::next(start, 2*(std::distance(start, i) + 1 ) );
    
    Iterator largest;
    
    if ((std::distance(leftChild,end) > 0) and (*leftChild > *i)) largest = leftChild;
    else largest = i;
    if ((std::distance(rightChild, end) > 0) and (*rightChild > *largest) ) largest = rightChild;
    
    if (largest != i){
        std::iter_swap(largest, i);
        max_heapify(start, end, largest);
    }
}

template <typename Iterator>
void build_heap (const Iterator start, const Iterator end){
    for (auto i = std::next(start, distance(start, end) / 2); i!=std::prev(start, 1); i-- ){
        max_heapify(start, end, i);
    }
}


template <typename Iterator>
void heapsort (Iterator start, Iterator end){
    build_heap(start, end);
    auto endUnsorted = end;
    for (auto i = std::prev(end,1); i!=start; i-- ){
        std::iter_swap(start, i);
        max_heapify(start, --endUnsorted, start);
    }
}



#endif
