#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6;
int n, m, k;
int f[maxn];
pair<int,int> s[maxn];

bool poss(int x) {
    vector<int> v(n+x);
    int p1 = 0, p2 = m-x;
    for (int i = 0; i < n+x; i++) {
        if (p1 == n) v[i] = s[p2++].first;
        else if (p2 == m) v[i] = f[p1++];
        else {
            if (f[p1] < s[p2].first) v[i] = f[p1++];
            else v[i] = s[p2++].first;
        }
    }
    int day = 0;
    int pt = 0;
    while (pt < v.size()) {
        if (v[pt] >= day) {
            pt += k;            
        }
        else return false;
        day++;
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        cin >> f[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> s[i].first;
        s[i].second = i+1;
    }
    sort(f,f+n);
    sort(s,s+m);
    if (!poss(0)) {
        cout << -1 << '\n';
    }
    else {
        int lo = 0, hi = m+1;
        while (lo + 1 < hi) {
            int mid = (lo+hi)/2;
            if (poss(mid)) lo = mid;
            else hi = mid;
        }
        //output lo last ones
        cout << lo << '\n';
        for (int i = 1; i <= lo; i++) {
            cout << s[m-i].second << ' ';
        }
        cout << '\n';
    }
}

