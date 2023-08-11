#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    pair<int,int> mx = {0,-1};
    for (int i = 0; i < n; i++) {
        mx = max(mx,{a[i],i});
    }
    int pos = mx.second;
    bool poss = true;
    for (int i = pos-1; i >= 0; i--) {
        if (a[i] > a[i+1]) poss = false;
    }
    for (int i = pos+1; i < n; i++) {
        if (a[i] > a[i-1]) poss = false;
    }
    cout << (poss ? "YES" : "NO") << '\n';
}
