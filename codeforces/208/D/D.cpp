#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 55;
int n, p[maxn], cost[5];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    ll curr = 0;
    vector<ll> ans(5,0);
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < 5; i++) {
        cin >> cost[i];
    }
    for (int i = 0; i < n; i++) {
        curr += a[i];
        for (int j = 4; j >= 0; j--) {
            ans[j] += curr/cost[j];
            curr %= cost[j];
        }
    }
    //output
    for (int i = 0; i < 5; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n' << curr << '\n';


    return 0;
}

