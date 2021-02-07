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
    vector<double> V = {1,6,3,5,0,2,7,9,8,4};
    cout << "VETTORE: "; print(V);
    
    insertionsort(V.begin(), V.end());
    
    cout << "VETTORE dopo IS: "; print(V);
    cout << *--V.end();
}
