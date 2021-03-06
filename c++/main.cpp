#include <fstream>
#include <chrono>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

#include "quicksort.cpp"
#include "mergesort.cpp"
#include "insertionsort.cpp"
#include "heapsort.cpp"

using namespace std;

/*
 
 ARGOMENTI MAIN (non conta l'ordine)
 
    '-trials=...'           -> ... = numero di prove (default 1)
    '-size=...'             -> ... = dimensione vettore (default 1000)
    '-seed=...'             -> ... = seed generatore num casuali (o '-seed=rnd' per random device )
    '-algo=...'             -> ... = algoritmo da testare (opzioni: STL, QS, IS, MS, HS o '-algo=all' per testarli tutti (default))

    '--randomized' o '-r'   -> usa randomized quicksort (default false)
    '--median'     o '-m'   -> usa metodo della mediana per pivot (default false)
 
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
    bool isRandom=false, median=false, isSorted=false, isReversed=false, Print=false, fewUnique=false, verbose=false, debug=false, randomSeed=false;
    string algo="_all_";
    
    {
    vector<string> input;
    for (int i=1; i<argc; i++) { input.push_back(string(argv[i])); }
        
    for (auto arg : input){
        if ( arg.find("-trials=") != -1 ) {trials = stoi(arg.erase(arg.find("-trials="),8));}
        if ( arg.find("-size=") != -1 ) {size = stoi(arg.erase(arg.find("-size="),6));}
        if ( (arg == "--randomized") or (arg=="-r") ) {isRandom = true;}
        if ( (arg == "--median") or (arg=="-m") ) {median = true;}
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
        if ( arg.find("-algo=") != -1 ) {
            algo="";
            if (arg.find("all") != -1 ) algo+="_all_";
            if (arg.find("STL") != -1 ) algo+="_STL_";
            if (arg.find("QS") != -1 ) algo+="_QS_";
            if (arg.find("IS") != -1 ) algo+="_IS_";
            if (arg.find("MS") != -1 ) algo+="_MS_";
            if (arg.find("HS") != -1 ) algo+="_HS_";
        }
    }
    }

//***********  TEST  ********************************************************************************************************//
    
    //Vettori per contenere i tempi di esecuzione
    vector<long long> trialsSTLsort, trialsInsertionsort, trialsQuicksort, trialsMergesort, trialsHeapsort;
    
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
        
        
        //STL sort
        if (algo.find("_STL_") != -1 or algo.find("_all_") != -1 ){
            auto vec = vec_;
            auto t1 = chrono::high_resolution_clock::now();
            sort(vec.begin(), vec.end());
            auto t2 = chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>( t2 - t1 ).count();
                        
            trialsSTLsort.push_back(duration);
        }
         
        
        //InsertionSort
        if (algo.find("_IS_") != -1 or algo.find("_all_") != -1 ){
            auto vec = vec_;
            auto t1 = std::chrono::high_resolution_clock::now();
            insertionsort(vec.begin(), vec.end());
            auto t2 = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>( t2 - t1 ).count();
            
            // se --debug controllo ordinamento
            if (debug and !is_sorted(vec.begin(), vec.end()) ) cerr << "\nErrore: Insertionsort non ordinato";
                
            trialsInsertionsort.push_back(duration);
        }
         
        
        //Quicksort
        if (algo.find("_QS_") != -1 or algo.find("_all_") != -1 ){
            auto vec = vec_;
            auto t1 = chrono::high_resolution_clock::now();
            quicksort(vec.begin(), vec.end(), isRandom, median);
            auto t2 = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::nanoseconds>( t2 - t1 ).count();
            
            // se --debug controllo ordinamento
            if (debug and !is_sorted(vec.begin(), vec.end()) ) cerr << "\nErrore: Quicksort non ordinato";
            
            trialsQuicksort.push_back(duration);
        }
         
        
        //Mergesort
        if (algo.find("_MS_") != -1 or algo.find("_all_") != -1 ){
            auto vec = vec_;
            auto t1 = std::chrono::high_resolution_clock::now();
            mergesort(vec.begin(), vec.end());
            auto t2 = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>( t2 - t1 ).count();
            
            // se --debug controllo ordinamento
            if (debug and !is_sorted(vec.begin(), vec.end()) ) cerr << "\nErrore: Mergesort non ordinato";
             
            trialsMergesort.push_back(duration);
        }
        
        //Heapsort
        if (algo.find("_HS_") != -1 or algo.find("_all_") != -1 ){
            auto vec = vec_;
            auto t1 = std::chrono::high_resolution_clock::now();
            heapsort(vec.begin(), vec.end());
            auto t2 = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>( t2 - t1 ).count();
            
            // se --debug controllo ordinamento
            if (debug and !is_sorted(vec.begin(), vec.end()) ) cerr << "\nErrore: Heapsort non ordinato";
             
            trialsHeapsort.push_back(duration);
        }
        
        
    }


//********  STAMPO RIEPILOGO SU TERMINALE  ***********************************************************************************************************//

    if (verbose){
        if (algo.find("_STL_") != -1  or algo.find("_all_") != -1 ) cout <<"\nTempo Medio STLsort: "<< int(accumulate(trialsSTLsort.begin(), trialsSTLsort.end(), 0.) / trialsSTLsort.size())<<" ns";
        if (algo.find("_IS_") != -1  or algo.find("_all_") != -1 ) cout <<"\nTempo Medio Insertionsort: "<< int(accumulate(trialsInsertionsort.begin(), trialsInsertionsort.end(), 0.) / trialsInsertionsort.size())<<" ns";
        if (algo.find("_QS_") != -1  or algo.find("_all_") != -1 ) cout <<"\nTempo Medio Quicksort: "<< int(accumulate(trialsQuicksort.begin(), trialsQuicksort.end(), 0.) / trialsQuicksort.size())<<" ns";
        if (algo.find("_MS_") != -1  or algo.find("_all_") != -1 ) cout <<"\nTempo Medio Mergesort: "<< int(accumulate(trialsMergesort.begin(), trialsMergesort.end(), 0.) / trialsMergesort.size())<<" ns";
        if (algo.find("_HS_") != -1  or algo.find("_all_") != -1 ) cout <<"\nTempo Medio Heapsort: "<< int(accumulate(trialsHeapsort.begin(), trialsHeapsort.end(), 0.) / trialsHeapsort.size())<<" ns";

    }
    
//********  STAMPO SU FILE  ***********************************************************************************************************//
    
    if (Print) {
        string sorted = isSorted ? "_InputOrdinato" : "";
        string random = isRandom ? "_Randomized" : "";
        string pochiVal = fewUnique ? "_pochiValori" : "";
        string size_ = to_string(size);

        ofstream os;
        
        if (algo.find("_STL_") != -1  or algo.find("_all_") != -1 ){
            os.open("./Risultati/STLsort/tempiOrdinamento_"+size_+"elementi"+sorted+pochiVal+".txt");
            for (int el : trialsSTLsort) {os << el << endl;}
            os.close();
        }

        if (algo.find("_QS_") != -1  or algo.find("_all_") != -1 ){
            os.open("./Risultati/Quicksort/tempiOrdinamento_"+size_+"elementi"+sorted+random+pochiVal+".txt");
            for (int el : trialsQuicksort) {os << el << endl;}
            os.close();
        }
                
        if (algo.find("_IS_") != -1  or algo.find("_all_") != -1 ){
             os.open("./Risultati/Insertionsort/tempiOrdinamento_"+size_+"elementi"+sorted+pochiVal+".txt");
            for (int el : trialsInsertionsort) {os << el << endl;}
            os.close();
        }
        
        
        if (algo.find("_MS_") != -1  or algo.find("_all_") != -1 ){
            os.open("./Risultati/Mergesort/tempiOrdinamento_"+size_+"elementi"+sorted+pochiVal+".txt");
            for (int el : trialsMergesort) {os << el << endl;}
            os.close();
        }
        if (algo.find("_HS_") != -1  or algo.find("_all_") != -1 ){
            os.open("./Risultati/Heapsort/tempiOrdinamento_"+size_+"elementi"+sorted+pochiVal+".txt");
            for (int el : trialsHeapsort) {os << el << endl;}
            os.close();
        }
         
    }
    
    cout << "\n" << endl;
    return 0;
}
