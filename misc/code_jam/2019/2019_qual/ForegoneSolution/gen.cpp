#include <bits/stdc++.h>
using namespace std;
using ll = long long;

typedef mt19937 rng_type;
rng_type rng;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int q; cin >> q;
    cout << q << '\n';
    rng.seed(rand());
    while (q--) {
        uniform_int_distribution<rng_type::result_type> udist(1,1000000000);
        int r = udist(rng);
        cout << r << '\n';
    }

}

