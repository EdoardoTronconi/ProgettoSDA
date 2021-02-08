#ifndef TESTER
#define TESTER

#include "quicksort.cpp"
#include "mergesort.cpp"
#include "insertionsort.cpp"

#include <algorithm>
#include <random>
#include <iostream>


template<typename Iterator>
class sorter{
protected:
    sorter(std::string algo): algo(algo) {}
    
    std::string algo;
    Iterator start, end;
    void sort(bool randomized=false) {
        switch (algo) {
            case algo=="STL":
                std::sort(start, end);
                break;
            case algo=="IS":
                insertionsort(start, end);
            case algo=="QS":
                quicksort(start, end, randomized);
            case algo=="MS":
                mergesort(start, end);
            default:
                std::cerr  << "\nNessun algoritmo scelto per Sorter" << std::endl;
                break;
        }
    }
};

template <typename Iterator>
class tester : public sorter<Iterator>{
private:
    int trials, size;
    bool isRandom, isSorted, Print, fewUnique, verbose, debug;
public:
    tester (std::string algo, Iterator start, Iterator end): sorter(algo), start(start), end(end)  {}
    
    void init (int trials, int size, bool isRandom, bool isSorted, bool Print, bool fewUnique, bool verbose, bool debug):
            trials(trials),
            size(size),
            isRandom(isRandom),
            isSorted(isSorted),
            Print(Print),
            fewUnique(fewUnique),
            verbose(verbose),
            debug(debug) {}
    
};
