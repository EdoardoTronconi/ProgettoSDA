/*
 ORDINA ELEMENTI NEL RANGE [start, end)
 */

#ifndef QUICKSORT
#define QUICKSORT

#include <random>
#include <utility>

// median_iter(A, B, C) = Iteratore a mediana(*A, *B, *C)
template <typename Iterator>
Iterator median_iter(Iterator A, Iterator B, Iterator C);


//*******  STANDARD QUICKSORT **********************************************//

template <typename Iterator>
Iterator partition(Iterator start, Iterator end, bool randomized, bool median){
    
    // se randomized scelgo casualmente il pivot
    if (randomized == true) {
        static std::mt19937_64 rnd(42);
        std::iter_swap(
                std::prev(end),
                next(start, rnd() % std::distance(start, end) )
                 );
        if (median and std::distance(start, end) > 4){
            std::iter_swap(
                    start,
                    next(start, rnd() % std::distance(start, end) )
                     );
            std::iter_swap(
                   next(start, std::distance(start, end) / 2),
                   next(start, rnd() % std::distance(start, end) )
                    );
        }
    }
    
    //scelgo come pivot l'ultimo elemento o la mediana(first, mid, last)
    if (median and std::distance(start, end) > 3) {
        std::iter_swap(
                median_iter(start, std::next(start, std::distance(start, end) / 2), std::prev(end) ),
                std::prev(end)
                      );
    }
    
    Iterator pivot = std::prev(end);
    
    //metto a sx tutti i valori minori di pivot e a dx tutti quelli maggiori
    Iterator i = start;
    for (auto j=start; j!=pivot; j++){
        if (*j <= *pivot) {std::iter_swap(i++,j);}
    }
    std::iter_swap(i,pivot);
    
    //restituisco un iteratore alla posizione in cui ho messo il pivot
    return i;
}

template <typename Iterator>
void quicksort(Iterator start, Iterator end, bool randomized=false, bool median=false){
    if (distance(start,end) > 1) {
        Iterator q = partition(start, end, randomized, median);
        quicksort(start, q, randomized, median);
        quicksort(std::next(q), end, randomized, median);
    }
}

//*******  3-WAY QUICKSORT **********************************************//

/*
nel loop:
[0 ... i-1 ; i ... j-1 ; j ... k-1 ; k ... ; pivot]
    |           |           |           |
    V           V           V           V
 < pivot     = pivot      liberi    > pivot
 
output:
[0 ... i-1 ; i ... j-1 ; j ... N]
     |           |           |
     V           V           V
  < pivot     = pivot      > pivot

*/

template <typename Iterator>
std::pair<Iterator, Iterator> three_way_partition(Iterator start, Iterator end, bool randomized, bool median){
    
    // se randomized scelgo casualmente il pivot
    if (randomized == true) {
        static std::mt19937_64 rnd(42);
        std::iter_swap(
                std::prev(end),
                next(start, rnd() % std::distance(start, end) )
                 );
        if (median and std::distance(start, end) > 3){
            std::iter_swap(
                    start,
                    next(start, rnd() % std::distance(start, end) )
                     );
            std::iter_swap(
                   next(start, std::distance(start, end) / 2),
                   next(start, rnd() % std::distance(start, end) )
                    );
        }
    }
    
    //scelgo come pivot l'ultimo elemento o la mediana(first, mid, last)
    if (median and std::distance(start, end) > 3) {
        std::iter_swap(
                median_iter(start, std::prev(end), std::next(start, std::distance(start, end) / 2) ),
                std::prev(end)
                      );
    }
 
    Iterator pivot = std::prev(end);

    auto i = start, j = start, k = prev(end);
    while (j != k)
        if (*j < *pivot)
            std::iter_swap(i++, j++);
        else if (*pivot < *j)
            std::iter_swap(j, --k);
        else
            ++j;

    std::iter_swap(j++, pivot);
    return {i, j};
}

template <typename Iterator>
void three_way_quicksort(Iterator start, Iterator end, bool randomized=false, bool median=false){
    if (distance(start,end) > 1) {
        std::pair<Iterator,Iterator> q = three_way_partition(start, end, randomized, median);
        three_way_quicksort(start, q.first, randomized, median);
        three_way_quicksort(q.second, end, randomized, median);
    }
}










//******** Iteratore alla mediana di tre *************************************************************//
template <typename Iterator>
Iterator median_iter(Iterator A, Iterator B, Iterator C){
    if (*A > *B)
        {
            if (*B > *C)
                return B;
            else if (*A > *C)
                return C;
            else
                return A;
        }
        else
        {
            if (*A > *C)
                return A;
            else if (*B > *C)
                return C;
            else
                return B;
        }
}



#endif
