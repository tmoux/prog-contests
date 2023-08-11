#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        vector<int> v;
        int n; cin >> n;
        for (int i = 0; i < n; i++) {
            int ai; cin >> ai;
            v.push_back(ai);
            while (v.size() >= 2) {
                if (v[v.size()-2] < v.back()) {
                    if (i == n-1) {
                        int j = v.back();
                        v.pop_back();
                        v.pop_back();
                        v.push_back(j);
                    }
                    else {
                        v.pop_back();
                    }
                }
                else break;
            }
        }
        /*
        for (auto i: v) {
            cout << i << ' ';
        }
        cout << '\n';
        */
        cout << ((v.size() == 1)?"YES":"NO") << '\n';
    }
}

