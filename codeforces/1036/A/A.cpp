#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll n, k; cin >> k >> n;
    cout << (n % k == 0 ? n/k : n/k+1) << '\n';

    return 0;
}

