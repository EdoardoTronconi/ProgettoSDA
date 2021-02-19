/*
 ORDINA ELEMENTI NEL RANGE [start, end)
 */

#ifndef HEAPSORT
#define HEAPSORT

#include <algorithm>

template <typename Iterator>
void max_heapify(const Iterator start, const Iterator end, Iterator i){
    
    Iterator leftChild = std::next(start, 2 * (std::distance(start, i)) + 1);
    Iterator rightChild = std::next(start, 2 * (std::distance(start, i) + 1 ) );
    
    Iterator largest = i;
    
    if ((std::distance(leftChild,end) > 0) and (*leftChild > *i)) largest = leftChild;
    if ((std::distance(rightChild, end) > 0) and (*rightChild > *largest) ) largest = rightChild;
    
    if (largest != i){
        std::iter_swap(largest, i);
        max_heapify(start, end, largest);
    }
}

template <typename BD_Iterator>
void build_heap (const BD_Iterator start, const BD_Iterator end){
    for (auto i = std::next(start, distance(start, end) / 2); i-- != start;){
        max_heapify(start, end, i);
    }
}


template <typename BD_Iterator>
void heapsort (BD_Iterator start, BD_Iterator end){
    build_heap(start, end);
    auto endUnsorted = end;
    for (auto i = std::prev(end); i!=start; i-- ){
        std::iter_swap(start, i);
        max_heapify(start, --endUnsorted, start);
    }
}



#endif
