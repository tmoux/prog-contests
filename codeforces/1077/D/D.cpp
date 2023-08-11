#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5+5;
int n, k;
vector<pair<int,int>> v;

bool check(int x) {
    int cnt = 0;
    for (auto i: v) cnt += i.first/x;
    return cnt >= k;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    map<int,int> mp;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        mp[ai]++;
    }
    for (auto& p: mp) v.push_back({p.second,p.first});
    sort(v.begin(),v.end(),[](pair<int,int>& a, pair<int,int>& b) {return a.first > b.first;});
    int lo = 0, hi = maxn;
    while (lo + 1 < hi) {
        int m = (lo+hi)>>1;
        bool is = check(m);
        (is ? lo : hi) = m;
    }
    //output
    for (int i = 0; i < v.size() && k; i++) {
        while (v[i].first >= lo && k) {
            v[i].first -= lo;
            cout << v[i].second << ' ';
            k--;
        }
    }

    return 0;
}

