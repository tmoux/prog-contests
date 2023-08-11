#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void sub_rev(string& s, int i, int j) {
    reverse(s.begin()+i,s.begin()+j+1);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    /*
    string s = "(())";
    reverse(s.begin()+1,s.begin()+3);
    cout << s << '\n';
    return 0;
    */
    int t; cin >> t;
    while (t--) {
        int n, k; cin >> n >> k;
        string s; cin >> s;
        vector<pair<int,int>> ans;
        string des;
        des.resize(n);
        int big = n/2-(k-1);
        for (int i = 0; i < big; i++) {
            des[i] = '(';
            des[i+big] = ')';
        }
        for (int i = 2*big; i < n; i++) {
            if (i&1) des[i] = ')';
            else des[i] = '(';
        }
        //cout << des << '\n';
        for (int i = 0; i < n; i++) {
            if (s[i] != des[i]) {
                //look for the first ) to reverse
                int k = -1;
                for (int j = i+1; j < n; j++) {
                    if (s[j] == des[i]) {
                        k = j;
                        break;
                    }
                }
                assert(k != -1);
                sub_rev(s,i,k);
                ans.push_back({i,k});
                //cout << i << ": " << s << endl;
            }
        }
        cout << ans.size() << '\n';
        for (auto p: ans) {
            cout << p.first+1 << ' ' << p.second+1 << '\n';
        }
    }
}

