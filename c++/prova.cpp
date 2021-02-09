#include <vector>
#include <iostream>
#include "insertionsort.cpp"
using namespace std;

template <typename T>
void print(vector<T> V){
    
    for (auto el : V){
        cout << el << " ";
    }
    cout << endl;
}

int main(){
    vector<double> V = {3,1,4,9,2};
    
    print(V);
    
    auto i = V.begin() + 1;
    
    *std::next(i) = *(i--);
    cout << endl << *(i+1) << endl;
    
    print(V);
    
}
