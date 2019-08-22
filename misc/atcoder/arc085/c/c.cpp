#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N, M;
    cin >> N >> M;
    int ans = 1900*M + 100*(N-M);
    while (M--) {
        ans *= 2;
    }
    cout << ans << '\n';
}

