#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    for (int qq = 1; qq <= t; qq++) {
        cout << "Case #" << qq << ": ";
        int N; cin >> N;
        N = 2*N-2;
        while (N--) {
            char c; cin >> c;
            cout << (c=='S'?'E':'S');
        }
        cout << '\n';
    }
}

