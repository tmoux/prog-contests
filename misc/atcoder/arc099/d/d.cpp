#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1000000;
double s[N+5], mn[N+5];
double S(int x) {
    int d = 0;
    int cp = x;
    while (cp > 0) {
        d += cp % 10;
        cp /= 10;
    }
    return (double)x/d;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    for (int i = N; i >= 1; i--) {
        s[i] = S(i);
        mn[i] = s[i];
        if (i < N) mn[i] = min(mn[i],mn[i+1]);
    }
    for (int i = 1; i <= N; i++) {
        if (s[i] <= mn[i+1]) {
            cout << i << '\n';
        }
    }
}

