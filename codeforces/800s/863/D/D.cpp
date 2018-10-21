#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5+5;
int n, q, m, a[maxn];

int lshift(int i, int l, int r) {
    if (i < l || i > r) return i;
    return i == l ? r : i-1;
}
int rev(int i, int l, int r) {
    if (i < l || i > r) return i;
    return r - (i-l);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> q >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    vector<pair<int,pair<int,int>>> qs(q);
    for (int i = 0; i < q; i++) {
        cin >> qs[i].first >> qs[i].second.first >> qs[i].second.second;
    }
    vector<int> b(m);
    for (int i = 0; i < m; i++) cin >> b[i];
    reverse(qs.begin(),qs.end());
    for (auto p: qs) {
        int t = p.first, l = p.second.first, r = p.second.second;
        for (int& i: b) {
            i = t == 1 ? lshift(i,l,r) : rev(i,l,r);    
        }
    }
    //output
    for (int i = 0; i < m; i++) {
        cout << a[b[i]] << ' ';
    }

    return 0;
}

