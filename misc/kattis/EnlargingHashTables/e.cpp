#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

map<int,bool> p;
bool isPrime(int x) {
    if (p.count(x)) return p[x];
    for (int j = 2; j*j <= x; j++) {
        if (x % j == 0) return p[x] = false;
    }
    return p[x] = true;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n;
    while (true) {
        cin >> n;
        if (n == 0) break;
        bool orig = isPrime(n);
        int nx = 2*n+1;
        while (!isPrime(nx)) nx++;
        cout << nx;
        if (orig) {
            cout << '\n';
        }
        else {
            cout << " (" << n << " is not prime)\n";
        }
    }

    return 0;
}

