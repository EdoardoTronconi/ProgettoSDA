/*
 ORDINA ELEMENTI NEL RANGE [start, end)
 */

#ifndef INSERTIONSORT
#define INSERTIONSORT
#include <iterator>

template <typename Iterator>
void insertionsort(Iterator start, Iterator end){
    for (auto j=std::next(start); j != end; j++){
        auto key = *j;
        Iterator i = std::prev(j);
        while ( (std::distance(start, i) >= 0) and (*i > key) ) {*(std::next(i)) = *(i); i--;}
        *(std::next(i)) = key;
    }
}

#endif

