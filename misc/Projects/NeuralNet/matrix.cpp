#ifndef MATRIX
#define MATRIX
#include <iostream>
#include <stdlib.h>
#include <exception>
#include <functional>
using namespace std;

class Matrix
{
    public:
        static const int MAXSZ = 10;
        double arr[MAXSZ][MAXSZ];
        int r, c;

        Matrix() {}

        Matrix(int rr, int cc) {
            r = rr;
            c = cc;
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < c; j++) {
                    arr[i][j] = (double)rand() / (double)RAND_MAX; 
                }
            }
        }

        Matrix(int rr, int cc, double A[][MAXSZ]) {
            r = rr;
            c = cc;
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < c; j++) {
                    arr[i][j] = A[i][j];
                }
            }
        }

        Matrix operator*(const Matrix& rhs) {
            //assumes c == rhs.r
            Matrix ret(r,rhs.c);
            if (c == rhs.r) {
                for (int i = 0; i < r; i++) {
                    for (int j = 0; j < rhs.c; j++) {
                        ret.arr[i][j] = 0;
                        for (int k = 0; k < c; k++) {
                            ret.arr[i][j] += arr[i][k]*rhs.arr[k][j];
                        }
                    }
                }
            }
            else {
                //cout << "AAAA!\n";
                //throw domain_error("Bad matrix multiplication!");
            }
            return ret;
        }

        Matrix& operator+=(const Matrix& rhs) {
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < c; j++) {
                    arr[i][j] += rhs.arr[i][j];
                }
            }
            return *this;
        }

        Matrix operator-(const Matrix & rhs) {
            Matrix ret(r,c);
            if (r == rhs.r && c == rhs.c) {
                for (int i = 0; i < r; i++) {
                    for (int j = 0; j < c; j++) {
                        ret.arr[i][j] = arr[i][j] - rhs.arr[i][j];
                    }
                }
            }
            return ret;
        }

        Matrix& operator-() {
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < c; j++) {
                    arr[i][j] = -arr[i][j];
                }
            }
            return *this;
        }

        Matrix T() {
            Matrix ret(c,r);
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < c; j++) {
                    ret.arr[j][i] = arr[i][j];
                }
            }
            return ret;
        }

        double norm() {
            double ret = 0;
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < r; j++) {
                    ret += arr[i][j]*arr[i][j];
                }
            }
            return ret;
        }

        Matrix operate(function<double(double)> f) {
            Matrix ret(r,c);
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < c; j++) {
                    ret.arr[i][j] = f(arr[i][j]);
                }
            }
            return ret;
        }

        Matrix scalarmult(const Matrix& rhs) {
            Matrix ret(r,c);
            if (c == rhs.c) {
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < c; j++) {
                    ret.arr[i][j] = arr[i][j]*rhs.arr[i][j];
                }
            }
            return ret;
            }
            else {
                if (c == 1) {
                    Matrix ret1(r,rhs.c);
                    for (int i = 0; i < r; i++) {
                        for (int j = 0; j < rhs.c; j++) {
                            ret1.arr[i][j] = arr[i][0] * rhs.arr[i][j];
                        }
                    }
                    return ret1;
                }
                else {
                    for (int i = 0; i < r; i++) {
                        for (int j = 0; j < c; j++) {
                            ret.arr[i][j] = arr[i][j] * rhs.arr[i][0];
                        }
                    }
                    return ret;
                }
            }
        }

        friend ostream& operator<< (ostream& stream, const Matrix& mat) {
            for (int i = 0; i < mat.r; i++) {
                for (int j = 0; j < mat.c; j++) {
                    stream << mat.arr[i][j] << ' ';
                }
                stream << '\n';
            }
            return stream;
        }
};
#endif
