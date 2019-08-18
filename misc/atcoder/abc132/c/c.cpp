#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int N, d[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> d[i];
    }
    sort(d,d+N);
    int ans = d[N/2] - d[N/2-1];
    cout << ans << '\n';
}

