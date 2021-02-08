#include <vector>
#include <iostream>
#include "heapsort.cpp"
using namespace std;

template <typename T>
void print(vector<T> V){
    
    for (auto el : V){
        cout << el << " ";
    }
    cout << endl;
}

int main(){
    vector<double> V = {2,1,7,6,9,8,3,4,5,10};
    
    print(V);
    
    heapsort(V.begin(), V.end());
    
    print(V);
    
}
