#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n;
ll b[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    ll mult = 1;
    int ans = 0;
    vector<ll> best;
    for (int i = 0; i <= 60; i++) {
        int cnt = 0;
        vector<ll> v;
        for (int j = 0; j < n; j++) {
            if (b[j] % mult == 0 && ((b[j]/mult) % 2) == 1) {
                cnt++;
            }
            else v.push_back(b[j]);
        }
        
        mult *= 2;
        if (cnt > ans) {
            ans = cnt;
            best = v;
        }
    }
    cout << (n-ans) << '\n';
    for (auto p: best) {
        cout << p << ' ';
    }
    if (!best.empty()) cout << '\n';
}
