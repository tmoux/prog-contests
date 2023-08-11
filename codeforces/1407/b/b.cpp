#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        multiset<int> a;
        for (int i = 0; i < n; i++) {
            int ai; cin >> ai;
            a.insert(ai);
        }
        vector<int> ans;
        ans.push_back(*a.rbegin());
        a.erase(prev(a.end()));

        int cur = ans.back();
        while (!a.empty()) {
            pair<int,int> mx = {0,-1};
            for (int i: a) {
                mx = max(mx,make_pair(__gcd(cur,i),i));
            }
            cur = mx.first;
            ans.push_back(mx.second);
            auto it = a.find(mx.second);
            a.erase(it);
        }
        for (auto i: ans) {
            cout << i << ' ';
        }
        cout << '\n';
    }
}
