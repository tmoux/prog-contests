#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 105;
int n;
string s[N];
vector<int> dir[N];
int deg[30];
int pos[N];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
    }
    for (int i = 1; i <= n; i++) {
        int ai; cin >> ai;
        pos[ai] = i;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (pos[i] >= pos[j]) continue;
            //now i comes before j in reordering
            for (unsigned k = 0; k < max(s[i].size(),s[j].size()); k++) {
                if (k == s[i].size()) {
                    //nothing
                    break;
                }
                else if (k == s[j].size()) {
                    //can't be
                    cout << "NE\n";
                    return 0;
                }
                else {
                    if (s[i][k] != s[j][k]) {
                        dir[s[i][k]-'a'].push_back(s[j][k]-'a');
                        deg[s[j][k]-'a']++;
                        break;
                    }
                }
            }
        }
    }
    //debug
    /*
    for (int i = 0; i < 26; i++) {
        cout << (char)(i+'a') << ": ";
        for (int j: dir[i]) {
            cout << (char)(j+'a') << ' ';
        }
        cout << '\n';
    }
    return 0;
    */
    //topsort
    queue<int> q;
    for (int i = 0; i < 26; i++) {
        if (deg[i] == 0) q.push(i);
    }
    vector<int> ord;
    while (!q.empty()) {
        int f = q.front(); q.pop();
        ord.push_back(f);
        for (int j: dir[f]) {
            if (--deg[j] == 0) {
                q.push(j);
            }
        }
    }
    if (ord.size() != 26) {
        cout << "NE\n";
        return 0;
    }
    else {
        vector<char> ans(26,0);
        for (int i = 0; i < 26; i++) {
            ans[ord[i]] = i+'a';
        }
        cout << "DA\n";
        for (int i = 0; i < 26; i++) {
            cout << ans[i];
        }
        cout << '\n';
    }
}
