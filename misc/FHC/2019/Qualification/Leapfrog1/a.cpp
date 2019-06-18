#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    for (int qq = 1; qq <= t; qq++) {
        cout << "Case #" << qq << ": ";
        string s; cin >> s;
        int n = s.size();
        int bc = 0;
        for (char c: s) if (c == 'B') bc++;
        cout << (n/2 <= bc && bc <= n-2 ? 'Y' : 'N') << '\n';
    }

}

