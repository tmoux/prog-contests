#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int nxt[200005];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; cin >> s;
    int n = s.size();
    set<int> zeros, ones;
    vector<int> start;
    for (int i = 0; i < n; i++) {
        if (s[i] == '0') {
            if (ones.empty()) {
                zeros.insert(i);
                start.push_back(i);
            }
            else {
                int j = *ones.begin();
                ones.erase(j);
                zeros.insert(i);
                nxt[j] = i;
            }
        }
        else {
            if (zeros.empty()) {
                cout << "-1\n";
                return 0;
            }
            else {
                int j = *zeros.begin();
                zeros.erase(j);
                ones.insert(i);
                nxt[j] = i;
            }
        }
    }
    if (!ones.empty()) {
        cout << -1 << '\n';
        return 0;
    }
    cout << start.size() << '\n';
    for (int i: start) {
        vector<int> v;
        int j = i;
        while (true) {
            v.push_back(j);
            j = nxt[j];
            if (j == 0) break;
        }
        cout << v.size() << ' ';
        for (auto j: v) {
            cout << j+1 << ' ';
        }
        cout << '\n';
    }
}

