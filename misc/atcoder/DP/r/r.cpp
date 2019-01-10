#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 51;
const int M = 1e9+7;
int N;
ll K;

void madd(int& a, int b) {
    a = (a+b) % M;
}

struct Matrix
{
    int m[maxn][maxn];
    int n;
    Matrix(int N_) {
        n = N_;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                m[i][j] = 0;
            }
        }
    }
};

Matrix operator*(Matrix a, Matrix b) {
    int n = a.n;
    Matrix res(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < N; k++) {
                madd(res.m[i][j],(1LL*a.m[i][k]*b.m[k][j])%M);
            }
        }
    }
    return res;
}

Matrix power(Matrix a, ll p) {
    int n = a.n;
    Matrix ans(a.n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ans.m[i][j] = (i==j);
        }
    }
    while (p) {
        if (p & 1) ans = ans * a;
        a = a * a;
        p >>= 1;
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> K;
    Matrix aa(N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> aa.m[i][j];
        }
    }
    Matrix ans = power(aa,K);
    int tot = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            madd(tot,ans.m[i][j]);
        }
    }
    cout << tot << '\n';


    return 0;
}

