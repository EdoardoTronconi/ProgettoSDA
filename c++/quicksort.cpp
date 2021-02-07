/*
 ORDINA ELEMENTI NEL RANGE [start, end)
 */

#ifndef QUICKSORT
#define QUICKSORT

#include <random>
/*
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
    for (auto j=start; j!=std::prev(end,1); j++){
        if (*j <= *pivot) {std::iter_swap(i++,j);}
    }
    std::iter_swap(i,pivot);
    
    //restituisco un iteratore alla posizione in cui ho messo il pivot
    return i;
}
*/

template <typename Iterator>
Iterator partition(Iterator start, Iterator end, bool randomized){
    
    // se randomized scambio l'ultimo elemento nel vettore con uno casuale
    if (randomized == true) {
        std::iter_swap(
                end - 1,
                next(start, rand() % std::distance(start, end) )
                 );
    }
    
    //scelgo come pivot l'indice dell'ultimo elemento
    Iterator pivot = end - 1;
    
    //metto a sx tutti i valori minori di pivot e a dx tutti quelli maggiori
    Iterator i = start;
    for (auto j=start; j!=end - 1; j++){
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
 

template <class Iterator>
inline void QuickSort(Iterator start, Iterator end, bool randomized=false) {
    
    if (distance(start,end) > 1){
        
        // se randomized scambio l'ultimo elemento nel vettore con uno casuale
        if (randomized == true) {
            std::swap(
                    *std::prev(end,1),
                    *next(start, rand() % std::distance(start, end) )
                     );
        }
        
        Iterator pivot = start, middle = start + 1;
        for (Iterator i = start + 1; i < end; ++i) {
            if (*i < *pivot) {
                std::iter_swap(i, middle);
                ++middle;
            }
        }
        std::iter_swap(start, middle - 1);
        QuickSort(start, middle - 1, randomized);
        QuickSort(middle, end, randomized);
    }
}

#endif
