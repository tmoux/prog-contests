#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m, k; cin >> n >> m >> k;
    cout << ((n <= min(m,k)) ? "Yes" : "No") << '\n';
}

