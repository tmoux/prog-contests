#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n;
int ans[1005];
set<int> ask(vector<int> v) {
    cout << "ASK ";
    cout << v.size() << ' ';
    for (auto i: v) {
        cout << i+1 << ' ';
    }
    cout << endl;
    set<int> res;
    for (int i = 0; i < v.size(); i++) {
        int ai; cin >> ai;
        ai--;
        res.insert(ai);
    }
    return res;
}

void rem(set<int>& s, set<int>& a) {
    for (int i: a) {
        if (s.count(i)) s.erase(i);
    }
}

set<int> v[10][2];

int main() {
    cin >> n;
    for (int i = 0; i < 10; i++) {
        vector<int> a;
        for (int j = 0; j < n; j++) {
            if (!(j & (1<<i))) a.push_back(j);
        }
        v[i][0] = ask(a);
        for (int j = 0; j < n; j++) {
            if (!v[i][0].count(j)) v[i][1].insert(j);
        }
        /*
        cout << i << ": " << 0 << '\n';
        for (auto j: v[i][0]) {
            cout << j << ' ';
        }
        cout << endl;
        cout << i << ": " << 1 << '\n';
        for (auto j: v[i][1]) {
            cout << j << ' ';
        }
        cout << endl;
        */
    }

    for (int i = 0; i < n; i++) {
        set<int> s;
        for (int j = 0; j < n; j++) s.insert(j);
        for (int d = 9; d >= 0; d--) {
            rem(s,v[d][(1&(i>>d))^1]);
            /*
            for (int j: s) {
                cout << j << ' ';
            }
            cout << endl;
            */
        }
        assert(!s.empty());
        ans[*s.begin()+1] = i+1;
    }
    //output
    cout << "ANSWER ";
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
    }
    cout << endl;
}
