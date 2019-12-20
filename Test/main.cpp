#include <iostream>

using namespace std;


int main() {
    double matrix[5][5];
    for(auto & i : matrix)
        for(double & j : i)
            j = 0.0;
        for(auto & i : matrix){
            for(double j : i)
                cout << j << " ";
            cout << endl;
        }

}
