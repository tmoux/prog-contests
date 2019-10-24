#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 3e5+5;
int a[N];
int n;

ll pre[N];
vector<int> v;

bool poss(int mid, int k) {
    auto it = upper_bound(v.begin(),v.end(),mid);
    int num = distance(it,v.end());
    num += pre[distance(v.begin(),it)-1]/mid;
    return num >= k;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    map<int,int> mp;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        mp[a[i]]++;
    }
    for (auto p: mp)
        v.push_back(p.second);
    sort(v.begin(),v.end());
    for (int i = 0; i < v.size(); i++) {
        pre[i] = v[i];
        if (i > 0) pre[i] += pre[i-1];
    }
    for (int k = 1; k <= n; k++) {
        int lo = 0, hi = n+1;
        while (lo + 1 < hi) {
            int mid = (lo+hi)/2;
            if (poss(mid,k)) {
                lo = mid;
            }
            else hi = mid;
        }
        cout << lo << '\n';
    }
}

