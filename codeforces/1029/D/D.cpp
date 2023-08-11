#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5+5;
int n, k, expo[11]; pair<int,int> A[maxn];
pair<int,int> convert(int i) {
    pair<int,int> ret = {0,0};
    if (i == 0) return {0,1};
    int mult = 1;
    while (i) {
        int r = i % 10;
        ret.first = (ret.first + r * mult) % k;
        mult = (mult * 10) % k;
        i /= 10;
        ret.second++;
    }
    return ret;
}

map<int,int> freq[11];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        auto it = convert(ai);
        A[i] = it;
        freq[it.second][it.first]++;
        //cout << ai << ' ' << it.first << ' ' << it.second << '\n';
    }
    expo[1] = 10 % k;
    for (int i = 2; i <= 10; i++) {
        expo[i] = (expo[i-1] * 10) % k;
    }
    ll ans = 0;
    //cout << '\n';
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= 10; j++) {
            ll curr = (1LL*A[i].first*expo[j]) % k;
            ll des = (k - curr) % k;
            if (freq[j].count(des)) ans += freq[j][des];
            //cout << curr << ' ' << des << ' ' << j << '\n';
            if (j == A[i].second && A[i].first == des) ans--;
        }
        //cout << ans << '\n';
    }
    cout << ans << '\n';

    return 0;
}

