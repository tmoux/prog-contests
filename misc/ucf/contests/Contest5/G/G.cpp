#include <bits/stdc++.h>
using namespace std;

const int maxn = 55;
int n;
double eqnsOrig[maxn][maxn+1];
double eqns[maxn][maxn+1];

int getMaxRow(int varI) {
	int res = varI;
	for (int i = varI + 1; i < n; i++) {
		if (abs(eqns[i][varI]) > abs(eqns[res][varI])) {
			res = i;
		}
	}
	return res;
}

void swapRows(int i, int j) {
	swap(eqns[i],eqns[j]);
}

void reduce(int i, int j) {
	double factor = eqns[j][i] / eqns[i][i];
	for (int k = i; k < n + 1; k++) {
		eqns[j][k] -= (factor*eqns[i][k]);
	}
}

bool getUpperTri() {
	for (int i = 0; i < n - 1; i++) {
		int best = getMaxRow(i);
		swapRows(i,best);
		if (abs(eqns[i][i] < 1e-9)) return false;
		for (int j = i + 1; j < n; j++) {
			reduce(i,j);
		}
	}
	return true;
}

double* solveIt() {
	double* res = new double[n];
	for (int i = n - 1; i >= 0; i--) {
		double c = eqns[i][n];
		for (int j = i + 1; i < n; j++) {
			c -= eqns[i][j]*res[j];
		}
		res[i] = c/eqns[i][i];
	}
	return res;
}

int main() {
	cin >> n;
	int C, L;
	cin >> C >> L;
	for (int i = 0; i < C; i++) {
		for (int j = 0; j < n; j++) {
			cin >> eqnsOrig[j][i];
		}
	}	
	for (int i = 0; i < L; i++) {
        for (int i = 0; i < C; i++) {
            for (int j = 0; j < n; j++) {
                eqns[j][i] = eqnsOrig[j][i];
            }
        }
        for (int j = 0; j < n; j++) {
            cin >> eqns[j][C];
        }
        if (getUpperTri()) {
            cout << "YES" << '\n';
        }
        else {
            cout << "NO" << '\n';
        }
    }
}
