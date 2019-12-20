#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        int c00 = 0, c01 = 0, c10 = 0, c11 = 0;
        vector<int> v00, v01, v10, v11;
        set<string> s;
        bool poss = true;
        vector<int> ans;
        vector<pair<string,int>> ps;
        bool seen01 = false;
        bool seen00 = false;
        bool seen11 = false;
        for (int i = 0; i < n; i++) {
            string ss; cin >> ss;
            if (s.count(ss)) {
                reverse(ss.begin(),ss.end());
                ans.push_back(i);
                if (s.count(ss)) {
                    poss = false;
                    break;
                }
                else {
                    s.insert(ss);
                    ps.push_back({ss,i});
                }
            }
            else {
                s.insert(ss);
                ps.push_back({ss,i});
            }
            if ((ss[0]=='0'&&ss.back()=='1')||(ss[0]=='1'&&ss.back()=='0')) {
                seen01 = true;
            }
            else if (ss[0]=='0'&&ss.back()=='0') {
                seen00 = true;
            }
            else if (ss[0]=='1'&&ss.back()=='1') {
                seen11 = true;
            }
        }
        for (auto p: ps) {
            auto ss = p.first;
            int i = p.second;
            auto sr = ss;
            reverse(sr.begin(),sr.end());
            if (s.count(sr)) continue;
            if (ss[0] == '0' && ss.back() == '0') {
                c00++;
                v00.push_back(i);
            }
            else if (ss[0] == '0' && ss.back() == '1') {
                c01++;
                v01.push_back(i);
            }
            else if (ss[0] == '1' && ss.back() == '0') {
                c10++;
                v10.push_back(i);
            }
            else if (ss[0] == '1' && ss.back() == '1') {
                c11++;
                v11.push_back(i);
            }
        }
        if (seen00 && seen11 && !seen01) {
            poss = false;
        }
        if (c01 > c10 + 1) {
            int add = (c01 - (c10))/2;
            for (int i = 0; i < add; i++) {
                ans.push_back(v01[i]);
            }
        }
        else if (c10 > c01 + 1) {
            int add = (c10 - (c01))/2;
            for (int i = 0; i < add; i++) {
                ans.push_back(v10[i]);
            }
        }
        if (!poss) {
            cout << -1 << '\n';
        }
        else {
            cout << ans.size() << '\n';
            for (auto i: ans) {
                cout << (i+1) << ' ';
            }
            cout << '\n';
        }
    }
}

