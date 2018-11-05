#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main()
{
    ll N, M, K, L; cin >> N >> M >> K >> L;
    ll x = (L+K) % M == 0 ? (L+K)/M : (L+K)/M+1;
    cout << (x*M > N ? -1 : x) << '\n';
    return 0;
}

