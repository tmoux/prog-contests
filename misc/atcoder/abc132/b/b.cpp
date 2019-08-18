#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }
    int cnt = 0;
    for (int i = 1; i < n-1; i++) {
        vector<int> v = {p[i-1],p[i],p[i+1]};
        sort(v.begin(),v.end());
        if (v[1] == p[i]) cnt++;
    }
    cout << cnt << '\n';
}

