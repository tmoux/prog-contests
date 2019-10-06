#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int N;

int f(int x) {
    if (x&1) return x>>1;
    return (x>>1)+(1<<(N-1));    
}

int main() {
    string X;
    cin >> N >> X;
    int x = 0;
    for (int i = 0; i < N; i++) {
        if (X[i] == '1') x |= (1<<i);
    }
    for (int i = 0; i <= x; i++) {
        int j = f(i);
        vector<int> it;
        it.push_back(i);
        it.push_back(j);
        for (int k = 0; k < 500; k++) {
            j = f(j);
            it.push_back(j);
            if (j == i) break;
        }
        cout << i << ": ";
        if (it.back() != j) {
            cout << 0 << '\n';
        }
        else {
            /*
            for (int k: it) {
                cout << k << ' ';
            }
            */
            cout << " (" << it.size()-1 << ")";

            cout << '\n';
        }
    }
}

