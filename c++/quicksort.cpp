/*
 ORDINA ELEMENTI NEL RANGE [start, end)
 */

#ifndef QUICKSORT
#define QUICKSORT

#include <random>


//*******  STANDARD QUICKSORT **********************************************//
template <typename Iterator>
Iterator partition(Iterator start, Iterator end, bool randomized, bool median){
    
    // se randomized scambio l'ultimo elemento nel vettore con uno casuale
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
    
    //scelgo come pivot l'ultimo elemento o la mediana(start, mid, end)
    if (median)
        iter_swap(
                  std::max(
                         std::min(  start  ,  std::prev(end) ),
                         std::min(  std::max(start,end)  ,  next(start, std::distance(start, std::prev(end)) / 2))
                         ),
                  std::prev(end));
    
    
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
[0 ... i-1 ; i ... j-1 ; j ... k-1 ; k ... ; pivot]
    |           |           |           |
    V           V           V           V
 < pivot     = pivot      liberi    > pivot
*/

template <typename Iterator>
std::pair<Iterator, Iterator> three_way_partition(Iterator start, Iterator end, bool randomized, bool median){
    
    // se randomized scambio l'ultimo elemento nel vettore con uno casuale
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
    
    //scelgo come pivot l'ultimo elemento o la mediana(start, mid, end)
    if (median)
        iter_swap(
                  std::max(
                         std::min(  start  ,  std::prev(end) ),
                         std::min(  std::max(start,end)  ,  next(start, std::distance(start, std::prev(end)) / 2))
                         ),
                  std::prev(end));
    
 
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

#endif
