#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxv = 7005;
int N, Q;
bitset<maxv> square_free, mobius[maxv];
vector<bitset<maxv>> vals;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    square_free.set();
    for (int i = 1; i < maxv; i++) {
        for (int p = 2; p*p <= i; p++) {
            if (i % (p*p) == 0) square_free[i] = 0;
        }
    }
    for (int i = 1; i < maxv; i++) {
        for (int j = 1; i*j < maxv; j++) {
            mobius[i][i*j] = square_free[j];
        }
    }

    cin >> N >> Q;
    vals.resize(N);
    while (Q--) {
        int type, x, y, z; cin >> type >> x >> y;
        x--;
        if (type == 2 || type == 3) {
            cin >> z;
            y--;
            z--;
        }
        if (type == 1) {
            vals[x].reset();
            for (int i = 1; i*i <= y; i++) {
                if (y % i == 0) {
                    vals[x][i] = 1;
                    vals[x][y/i] = 1;
                }
            }
        }
        else if (type == 2) {
            vals[x] = vals[y] ^ vals[z];
        }
        else if (type == 3) {
            vals[x] = vals[y] & vals[z];
        }
        else {
            int c = (vals[x] & mobius[y]).count() % 2;
            putchar(c==0?'0':'1');
        }
    }
    cout << '\n';

    for (int i = 1; i <= 1; i++) {
        for (int j = 0; j < 100; j++) {
            cout << j << ": " << mobius[1][j] << '\n';
        }
    }

    return 0;
}

