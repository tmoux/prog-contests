#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int has4(int x) {
    while (x) {
        if (x % 10 == 4) return true;
        x /= 10;
    }
    return false;
}

int main()
{
    int t; cin >> t;
    mt19937 rng;
    mt19937::result_type const seed = 6969;
    rng.seed(seed);
    for (int qq = 1; qq <= t; qq++) {
        int N; cin >> N;
        uniform_int_distribution<mt19937::result_type> udist(0,N);
        while (true) {
            int r = udist(rng);
            //cout << N << ": " << r << '\n';
            if (!has4(r) && !has4(N-r)) {
                printf("Case #%d: %d %d\n",qq,r,N-r);
                break;
            }
        }
    }
}

