#include <fstream>
#include <chrono>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>


#include "quicksort.cpp"

using namespace std;

/*
 
 ARGOMENTI MAIN (non conta l'ordine)
 
    '-trials=...'           -> ... = numero di prove (default 1)
    '-size=...'             -> ... = dimensione vettore (default 1000)
    '-seed=...'             -> ... = seed generatore num casuali (o '-seed=rnd' per random device )
 
    '--sorted'     o '-s'   -> ordina un vettore già ordinato (default false)
    '--reversed'            -> ordina un vettore già ordinato in modo decrescente (default false)
    '--fewUnique'           -> ordina un vettore con pochi valori distinti (default false)
 
    '--verbose'    o '-v'   -> stampa su terminale riepilogo (default false)
    '--file'       o '-f'   -> stampa su file il risultato (default false)
    '--debug'               -> controlla se gli algoritmi di ordinamento funzionano e stampa errore in caso contrario

*/

int main(int argc, char * argv[]) {
    
        
//***********  CONVERSIONE ARGOMENTI  *******************************************************************//
    
    int trials=1, size=1000, seed=0;
    bool isRandom=false, isSorted=false, isReversed=false, Print=false, fewUnique=false, verbose=false, debug=false, randomSeed=false;
    
    {
    vector<string> input;
    for (int i=1; i<argc; i++) { input.push_back(string(argv[i])); }
        
    for (auto arg : input){
        if ( arg.find("-trials=") != -1 ) {trials = stoi(arg.erase(arg.find("-trials="),8));}
        if ( arg.find("-size=") != -1 ) {size = stoi(arg.erase(arg.find("-size="),6));}
        if ( (arg == "--sorted") or (arg=="-s") ) {isSorted = true;}
        if ( (arg == "--reversed") ) {isReversed=true;}
        if ( (arg == "--file") or (arg=="-f")) {Print = true;}
        if ( arg == "--fewUnique" ) {fewUnique = true;}
        if ( ( arg == "--verbose" ) or ( arg == "-v" ) ) {verbose=true;}
        if ( arg == "--debug" ) {debug = true;}
        if ( arg.find("-seed=") != -1 ) {
            if (arg=="-seed=rnd") {randomSeed=true;}
            else { seed = stoi( arg.erase(arg.find("-seed="),6));}
        }
    }
    }

//***********  TEST  ********************************************************************************************************//
    
    //Vettori per contenere i tempi di esecuzione
    vector<long long> standardQS, randomizedQS, medianQS, randomizedMedianQS, threeWayQS, randomizedThreeWayQS, randomizedMedianThreeWayQS;
    
    standardQS.reserve(trials);
    randomizedQS.reserve(trials);
    threeWayQS.reserve(trials);
    randomizedThreeWayQS.reserve(trials);
    
    //Generatore di numeri casuali
    mt19937_64 rng(seed);
    if (randomSeed){
        random_device rd;
        rng.seed(rd());
    }
    
    
    //Ripeto per Trials volte
    for (int trial=1; trial<=trials; trial++){
        
        // creo vettore da ordinare
        vector<double> vec_(size);
        if (fewUnique){
            for (int i=0; i<size; i++) {vec_[i] = rng() % 3;}
        }
        else{
            for (int i=0; i<size; i++) {vec_[i] = double(rng()) / rng.max(); }
        }
        
        // Ordino se ho opzioni --sorted / --reversed
        if(isSorted) {sort(vec_.begin(), vec_.end());}
        if(isReversed) {sort(vec_.begin(), vec_.end()); reverse(vec_.begin(), vec_.end());}
        
        
        //Standard QS
        {
            auto vec = vec_;
            auto t1 = chrono::high_resolution_clock::now();
            quicksort(vec.begin(), vec.end());
            auto t2 = chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>( t2 - t1 ).count();
                        
            standardQS.push_back(duration);
            
            if (debug) {if (!is_sorted(vec.begin(), vec.end())) cerr<<"\nErrore: standardQS non ordinato!";}
        }
        
        //Median QS
        {
            auto vec = vec_;
            auto t1 = chrono::high_resolution_clock::now();
            quicksort(vec.begin(), vec.end(), false, true);
            auto t2 = chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>( t2 - t1 ).count();
                        
            medianQS.push_back(duration);
            
            if (debug) {if (!is_sorted(vec.begin(), vec.end())) cerr<<"\nErrore: medianQS non ordinato!";}
        }
         
        
        //Randomized QS
        {
            auto vec = vec_;
            auto t1 = chrono::high_resolution_clock::now();
            quicksort(vec.begin(), vec.end(), true, false);
            auto t2 = chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>( t2 - t1 ).count();
                        
            randomizedQS.push_back(duration);
            
            if (debug) {if (!is_sorted(vec.begin(), vec.end())) cerr<<"\nErrore: randomizedQS non ordinato!";}
        }
        
        //Randomized Median QS
        {
            auto vec = vec_;
            auto t1 = chrono::high_resolution_clock::now();
            quicksort(vec.begin(), vec.end(), true, true);
            auto t2 = chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>( t2 - t1 ).count();
                        
            randomizedMedianQS.push_back(duration);
            
            if (debug) {if (!is_sorted(vec.begin(), vec.end())) cerr<<"\nErrore: randomizedMedianQS non ordinato!";}
        }
         
        
        //Three Way QS
        {
            auto vec = vec_;
            auto t1 = chrono::high_resolution_clock::now();
            three_way_quicksort(vec.begin(), vec.end());
            auto t2 = chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>( t2 - t1 ).count();
                        
            threeWayQS.push_back(duration);
            
            if (debug) {if (!is_sorted(vec.begin(), vec.end())) cerr<<"\nErrore: threeWayQS non ordinato!";}
        }
         
        
        //Randomized Three Way QS
        {
            auto vec = vec_;
            auto t1 = chrono::high_resolution_clock::now();
            three_way_quicksort(vec.begin(), vec.end(), true, false);
            auto t2 = chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>( t2 - t1 ).count();
                        
            randomizedThreeWayQS.push_back(duration);
            
            if (debug) {if (!is_sorted(vec.begin(), vec.end())) cerr<<"\nErrore: randomizedThreeWayQS non ordinato!";}
        }
        
        //Randomized Median Three Way QS
        {
            auto vec = vec_;
            auto t1 = chrono::high_resolution_clock::now();
            three_way_quicksort(vec.begin(), vec.end(), true, true);
            auto t2 = chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>( t2 - t1 ).count();
                        
            randomizedMedianThreeWayQS.push_back(duration);
            
            if (debug) {if (!is_sorted(vec.begin(), vec.end())) cerr<<"\nErrore: randomizedMedianThreeWayQS non ordinato!";}
        }
    }


//********  STAMPO RIEPILOGO SU TERMINALE  ***********************************************************************************************************//

    if (verbose){
        cout <<"\nTempo Medio Standard QS: "<< int(accumulate(standardQS.begin(), standardQS.end(), 0.) / standardQS.size())<<" ns";
        cout <<"\nTempo Medio Randomized QS: "<< int(accumulate(randomizedQS.begin(), randomizedQS.end(), 0.) / randomizedQS.size())<<" ns";
        cout <<"\nTempo Medio Median QS: "<< int(accumulate(medianQS.begin(), medianQS.end(), 0.) / medianQS.size())<<" ns";
        cout <<"\nTempo Medio Randomized Median QS: "<< int(accumulate(randomizedMedianQS.begin(), randomizedMedianQS.end(), 0.) / randomizedMedianQS.size())<<" ns";
        cout <<"\nTempo Medio Three Way QS: "<< int(accumulate(threeWayQS.begin(), threeWayQS.end(), 0.) / threeWayQS.size())<<" ns";
        cout <<"\nTempo Medio Randomized Three Way QS: "<< int(accumulate(randomizedThreeWayQS.begin(), randomizedThreeWayQS.end(), 0.) / randomizedThreeWayQS.size())<<" ns";
        cout <<"\nTempo Medio Randomized Median Three Way QS: "<< int(accumulate(randomizedMedianThreeWayQS.begin(), randomizedMedianThreeWayQS.end(), 0.) / randomizedMedianThreeWayQS.size())<<" ns";
    }
    
//********  STAMPO SU FILE  ***********************************************************************************************************//
    
    if (Print) {

        ofstream os;
        
        os.open("./Risultati/Quicksort/tempiOrdinamento_standardQS.txt");
        for (int el : standardQS) {os << el << endl;}
        os.close();
        
        os.open("./Risultati/Quicksort/tempiOrdinamento_randomizedQS.txt");
        for (int el : randomizedQS) {os << el << endl;}
        os.close();
        
        os.open("./Risultati/Quicksort/tempiOrdinamento_medianQS.txt");
        for (int el : medianQS) {os << el << endl;}
        os.close();
        
        os.open("./Risultati/Quicksort/tempiOrdinamento_randomizedMedianQS.txt");
        for (int el : randomizedMedianQS) {os << el << endl;}
        os.close();
        
        os.open("./Risultati/Quicksort/tempiOrdinamento_threeWayQS.txt");
        for (int el : threeWayQS) {os << el << endl;}
        os.close();
        
        os.open("./Risultati/Quicksort/tempiOrdinamento_randomizedThreeWayQS.txt");
        for (int el : randomizedThreeWayQS) {os << el << endl;}
        os.close();
        
        os.open("./Risultati/Quicksort/tempiOrdinamento_randomizedMedianThreeWayQS.txt");
        for (int el : randomizedMedianThreeWayQS) {os << el << endl;}
        os.close();
 
    }
    cout << endl;
    return 0;
}
