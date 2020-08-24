#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    multiset<int> ms;
    int numAdd = 0;
    vector<pair<string,int>> ans;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        if (s == "insert") {
            int k; cin >> k;
            ms.insert(k);

            ans.push_back({"insert",k});
        }
        else if (s == "getMin") {
            int k; cin >> k;
            while (!ms.empty() && *ms.begin() < k) {
                ans.push_back({"removeMin",0});
                ms.erase(ms.begin());
            }
            if (ms.empty() || *ms.begin() != k) {
                ms.insert(k);
                ans.push_back({"insert",k});
            }
            ans.push_back({"getMin",k});
        }
        else {
           if (ms.empty()) {
               ans.push_back({"insert",-1000000000});
               ms.insert(-1000000000);
           }
           ans.push_back({"removeMin",0});
           assert(!ms.empty());
           ms.erase(ms.begin());
        }
    }
    cout << ans.size() << '\n';
    for (auto p: ans) {
        cout << p.first;
        if (p.first[0] == 'r') {
            cout << '\n';
        }
        else {
            cout << ' ' << p.second << '\n';
        }
    }
}

