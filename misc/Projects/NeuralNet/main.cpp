#include <iostream>
#include <algorithm>
#include <math.h>
#include <time.h>
#include "matrix.cpp"
#include "neural.cpp"
using namespace std;
typedef double matarr[Matrix::MAXSZ][Matrix::MAXSZ];


int main()
{
    srand(time(NULL));
    NeuralNet nn;
    matarr inputs[4] = {{0,0},{0,1},{1,0},{1,1}};
    matarr res[4] = {{0},{1},{1},{0}};
    pair<Matrix,Matrix> ins[4];
    for (int i = 0; i < 4; i++) {
        ins[i] = {Matrix(2,1,inputs[i]),Matrix(1,1,res[i])};
    }
    for (int i = 0; i < 1000; i++) {
        int r = rand() % 4;
        nn.backprop(ins[r].first,ins[r].second);
    }

    for (int i = 0; i < 4; i++) {
        nn.feedFwd(ins[i].first);
        cout << "Testing: " << (i%2) << ' ' << (i/2) << '\n';
        cout << "Result: " << nn.Y << '\n';
    }
     
    return 0;
}
	

