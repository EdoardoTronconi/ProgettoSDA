/*
 ORDINA ELEMENTI NEL RANGE [start, end)
 */

#ifndef QUICKSORT
#define QUICKSORT

#include <random>

template <typename Iterator>
Iterator partition(Iterator start, Iterator end, bool randomized){
    
    // se randomized scambio l'ultimo elemento nel vettore con uno casuale
    if (randomized == true) {
        std::iter_swap(
                std::prev(end,1),
                next(start, rand() % std::distance(start, end) )
                 );
    }
    
    //scelgo come pivot l'indice dell'ultimo elemento
    Iterator pivot = std::prev(end,1);
    
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
        quicksort(q+1, end, randomized);
    }
}

#endif
