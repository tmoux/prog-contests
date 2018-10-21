#ifndef NEURAL
#define NEURAL
#include <iostream>
#include <algorithm>
#include <math.h>
#include "matrix.cpp"
using namespace std;
typedef double matarr[Matrix::MAXSZ][Matrix::MAXSZ];

class NeuralNet
{
    public:
        static const int NUMX = 3;
        static const int NUMZ = 4;
        static const int NUMY = 1;
        Matrix W1;
        Matrix W2;
        Matrix X, Z1, A1, Z2, Y;

        NeuralNet() {
            W1 = Matrix(NUMZ,NUMX);
            W2 = Matrix(NUMY,NUMZ);
            X = Matrix(NUMX,1);
            Z1 = Matrix(NUMZ,1);
            A1 = Matrix(NUMZ,1);
            Z2 = Matrix(NUMY,1);
            Y = Matrix(NUMY,1);
        }

        static double sigmoid(double x) {
            return 1.0/(1+exp(x));
        }
        
        static double dSigmoid(double x) {
            return sigmoid(x)*(1.0-sigmoid(x));
        }

        void feedFwd(const Matrix& input) {
            X = input;
            Z1 = (W1*X);
            A1 = Z1.operate(sigmoid);
            Z2 = W2*A1;
            Y = Z2.operate(sigmoid);
        }

        void backprop(const Matrix& input, const Matrix& y) {
            feedFwd(input); //Y is y-hat, y is actual value
            
            double loss = (Y-y).norm();
            cout << loss << '\n';
            Matrix delta3 = (Y-y).scalarmult(Z2.operate(dSigmoid));
            Matrix dJdW2 = A1.T() * delta3;

            Matrix delta2 = (delta3.scalarmult(W2.T())).scalarmult(Z1.operate(dSigmoid));
            Matrix dJdW1 = X.T() * delta2;

            W1 += dJdW1;
            W2 += dJdW2;
        }
        

};
#endif
	

