#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline int lg(int x) { return 32 - __builtin_clz(x) - 1;}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    cout << lg(n) + 1 << '\n';

    return 0;
}

