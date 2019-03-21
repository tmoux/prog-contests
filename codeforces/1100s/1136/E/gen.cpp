#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::mt19937 gen(seed);  // mt19937 is a standard mersenne_twister_engine
    int n; cin >> n;
    cout << n << '\n';
    vector<int> k(n-1);
    for (int i = 0; i < n - 1; i++) {
        k[i] = (gen() % 20) - 10;
    }
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        int ai = (gen() % 20) - 10;
        if (i > 0) ai = max(ai,a[i-1]+k[i-1]);
        a[i] = ai;
        cout << ai << ' ';
    }
    cout << '\n';
    for (int i = 0; i < n - 1; i++) {
        cout << k[i] << ' ';
    }
    cout << '\n';
    
    cout << n << '\n';
    for (int i = 0; i < n; i++) {
        int t = rand() % 2;
        if (t == 0) {
            cout << "+ ";
            int i = (gen() % n) + 1;
            int x = gen() % 10;
            cout << i << ' ' << x << '\n';
        }
        else {
            cout << "s ";
            int l = gen() % n + 1;
            int r = gen() % n + 1;
            if (l > r) swap(l,r);
            cout << l << ' ' << r << '\n';
        }
    }
}

