#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    map<int,int> mp;
    for (int i = 0; i < n; i += 2) {
        mp[v[i]]++;
    }
    vector<pair<int,int>> even;
    for (auto p: mp) {
        even.push_back(p);
    }
    even.push_back({0,0});
    sort(even.begin(),even.end(),[](auto a, auto b) {
            return a.second > b.second;
            });

    map<int,int> mp2;
    for (int i = 1; i < n; i += 2) {
        mp2[v[i]]++;
    }
    vector<pair<int,int>> odd;
    for (auto p: mp2) {
        odd.push_back(p);
    }
    odd.push_back({-1,0});
    sort(odd.begin(),odd.end(),[](auto a, auto b) {
            return a.second > b.second;
            });
    if (even[0].first != odd[0].first) {
        int ans = (n/2-even[0].second) + (n/2-odd[0].second);
        cout << ans << '\n';
    }
    else {
        int a1 = (n/2-even[1].second) + (n/2-odd[0].second);
        int a2 = (n/2-even[0].second) + (n/2-odd[1].second);
        cout << min(a1,a2) << '\n';
    }
}

