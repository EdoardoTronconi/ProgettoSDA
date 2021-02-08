/*
 ORDINA ELEMENTI NEL RANGE [start, end)
*/

#ifndef MERGESORT
#define MERGESORT
#include <vector>

template <class Iterator>
void merge(Iterator start, Iterator middle, Iterator end){
    
    std::vector<typename Iterator::value_type> buffer;
    buffer.reserve(std::distance(start, end));
    
    Iterator left(start), right(middle);
    const Iterator mid_(middle), end_(end);
    
    while ((left != mid_) and (right != end_) ) buffer.push_back( (*left <= *right) ? *left++ : *right++);
    
    buffer.insert(buffer.end(), left, mid_);
    buffer.insert(buffer.end(), right, end_);
    
    std::move(buffer.begin(), buffer.end(), start);
    
}


template <class Iterator>
inline void mergesort(Iterator start, Iterator end) {
    if (distance(start,end)>1){
        Iterator middle = start + distance(start,end)/2;
        
        mergesort(start, middle);
        mergesort(middle, end);
        
        merge(start, middle, end);
    }
}


#endif
