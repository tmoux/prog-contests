#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    string s; cin >> s;
    int n = s.size();
    int ac = 0;
    for (char c: s) if (c == 'a') ac++;
    if (ac*2 > n) {
        cout << n << '\n';
    }
    else {
        cout << (ac*2-1) << '\n';
    }
}

