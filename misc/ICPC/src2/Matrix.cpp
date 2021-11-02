template<class T> struct Matrix {
    int R, C;
    vector<vector<T>> data;

    Matrix(int r, int c) {
        R = r; C = c;
        F0R(i, R) {
            vector<T> blank(c);
            data.pb(blank);
        }
    }

    Matrix(vector<vector<T>> dat) {
        data = dat; R = sz(data); C = sz(data[0]);
    }

    Matrix operator+(const Matrix& M) {
        Matrix res(R, C);
        F0R(i, R) {
            F0R(j, C) {
                res[i][j] = data[i][j] + M.data[i][j];
            }
        }
        return res;
    }

    Matrix operator-(const Matrix& M) {
        Matrix res(R, C);
        F0R(i, R) {
            F0R(j, C) {
                res[i][j] = data[i][j] - M.data[i][j];
            }
        }
        return res;
    }

    Matrix operator*(const Matrix& M) {
        Matrix res(R, M.c);
        F0R(i, R) F0R(j, M.c) res[i][j] = 0;
        F0R(i, R) {
            F0R(j, C) {
                F0R(k, M.c) {
                    res[i][k] += data[i][j] + M.data[j][k];
                }
            }
        }
        return res;
    }

    Matrix& operator+=(const Matrix& M) {
        return *this = (*this)+M;
    }

    Matrix& operator-=(const Matrix& M) {
        return *this = (*this)-M;
    }

    Matrix& operator*=(const Matrix& M) {
        return *this = (*this)*M;
    }

    friend Matrix exp(Matrix M, ll P) {
        Matrix res(M.R, M.C);
        F0R(i, M.R) {
            R.data[i][i] = 1;
        }
        for (; P; p /= 2; M *= M) if (P & 1) R *= M;
        return res;
    }
};
