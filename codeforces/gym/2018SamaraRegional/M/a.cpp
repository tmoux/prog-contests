#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    vector<string> a(3); cin >> a[0] >> a[1] >> a[2];
    int n = a[0].size();
    vector<int> pos;
    for (int i = 0; i < n; i++) {
        if (a[0][i] != a[1][i] || a[1][i] != a[2][i] || a[0][i] != a[2][i]) {
            pos.push_back(i);
        }
    }
    if (pos.size() <= 1) {
        cout << "Ambiguous\n";
    }
    else if (pos.size() > 3) {
        cout << "Impossible\n";
    }
    else {
        set<string> ans;
        auto valid = [](const string& real, const vector<string>& v) {
            for (int i = 0; i < 3; i++) {
                int diff = 0;
                for (int j = 0; j < v[i].size(); j++) {
                    diff += real[j] != v[i][j];
                }
                if (diff > 1) return false;
            }
            return true;
        };
        if (pos.size() == 2) {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    string real = a[0];
                    real[pos[0]] = a[i][pos[0]];
                    real[pos[1]] = a[j][pos[1]];
                    if (valid(real,a)) ans.insert(real);
                }
            }
        }
        else if (pos.size() == 3) {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    for (int k = 0; k < 3; k++) {
                        string real = a[0];
                        real[pos[0]] = a[i][pos[0]];
                        real[pos[1]] = a[j][pos[1]];
                        real[pos[2]] = a[k][pos[2]];
                        if (valid(real,a)) ans.insert(real);
                    }
                }
            }
        }
        else assert(false);
        if (ans.empty()) {
            cout << "Impossible\n";
        }
        else if (ans.size() == 1) {
            cout << *ans.begin() << '\n'; 
        }
        else {
            cout << "Ambiguous\n";
            /*
            for (auto i: ans) {
                cout << i << endl;
            }
            */
        }
    }
}
