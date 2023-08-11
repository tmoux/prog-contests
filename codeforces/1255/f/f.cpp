#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll q1(int i, int j, int k) {
    printf("1 %d %d %d\n",i,j,k);
    fflush(stdout);
    ll a; cin >> a;
    return a;
}

int q2(int i, int j, int k) {
    printf("2 %d %d %d\n",i,j,k);
    fflush(stdout);
    int a; cin >> a;
    return a;
}

int main() {
    int n; cin >> n;
    int mn = n;
    for (int i = 2; i < n; i++) {
        int sign = q2(1,i,mn);
        if (sign == 1) {
            mn = i;
        }
    }
    vector<ll> areas(n+1);
    //now i and mn are adjacent
    pair<ll,int> best = {0LL,-1};
    for (int i = 2; i <= n; i++) {
        if (i == mn) continue;
        ll area = q1(1,mn,i);
        areas[i] = area;
        best = max(best,{area,i});
    }
    vector<pair<ll,int>> pos, neg;
    int mx = best.second;
    for (int i = 2; i <= n; i++) {
        if (i == mn || i == mx) continue;
        int sign = q2(1,mx,i);
        if (sign == 1) {
            pos.push_back({areas[i],i});
        }
        else {
            neg.push_back({areas[i],i});
        }
    }
    sort(neg.begin(),neg.end());
    sort(pos.begin(),pos.end(),greater<pair<ll,int>>());
    //output
    cout << "0 1 ";
    cout << mn << ' ';
    for (auto p: neg) {
        cout << p.second << ' ';
    }
    cout << mx << ' ';
    for (auto p: pos) {
        cout << p.second << ' ';
    }
    cout << '\n';
}

