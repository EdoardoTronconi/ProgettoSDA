/*
 ORDINA ELEMENTI NEL RANGE [start, end)
 */

#ifndef QUICKSORT
#define QUICKSORT

#include <random>


//*******  STANDARD QUICKSORT **********************************************//
template <typename Iterator>
Iterator partition(Iterator start, Iterator end, bool randomized){
    
    // se randomized scambio l'ultimo elemento nel vettore con uno casuale
    if (randomized == true) {
        std::iter_swap(
                std::prev(end),
                next(start, rand() % std::distance(start, end) )
                 );
    }
    
    //scelgo come pivot l'indice dell'ultimo elemento
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
void quicksort(Iterator start, Iterator end, bool randomized=false){
    if (distance(start,end) > 1) {
        Iterator q = partition(start, end, randomized);
        quicksort(start, q, randomized);
        quicksort(std::next(q), end, randomized);
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
std::pair<Iterator, Iterator> three_way_partition(Iterator start, Iterator end, bool randomized){
    
    // se randomized scambio l'ultimo elemento nel vettore con uno casuale
    if (randomized == true) {
        std::iter_swap(
                std::prev(end),
                next(start, rand() % std::distance(start, end) )
                 );
    }
    
    const auto pivot = *std::prev(end);

    auto i = start, j = start, k = prev(end);
    while (j != k)
        if (*j < pivot)
            std::iter_swap(i++, j++);
        else if (pivot < *j)
            std::iter_swap(j, --k);
        else
            ++j;

    std::iter_swap(j++, prev(end));
    return {i, j};
}

template <typename Iterator>
void three_way_quicksort(Iterator start, Iterator end, bool randomized=false){
    if (distance(start,end) > 1) {
        std::pair<Iterator,Iterator> q = three_way_partition(start, end, randomized);
        three_way_quicksort(start, q.first, randomized);
        three_way_quicksort(q.second, end, randomized);
    }
}

#endif
