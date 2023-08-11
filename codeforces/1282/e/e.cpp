#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n;

struct tri
{
    int a, b, c, id;
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        cin >> n;
        vector<int> cnt(n+1);
        vector<vector<tri>> tris(n+1,vector<tri>());
        vector<int> ord;
        vector<vector<int>> ans(n+1,vector<int>());
        for (int i = 1; i <= n-2; i++) {
            int a, b, c; cin >> a >> b >> c;
            cnt[a]++; cnt[b]++; cnt[c]++;
            tris[a].push_back({a,min(b,c),max(b,c),i});
            tris[b].push_back({b,min(a,c),max(a,c),i});
            tris[c].push_back({c,min(a,b),max(a,b),i});
        }
        if (n == 3) {
            cout << "1 2 3\n1\n";
            continue;
        }
        queue<int> q;
        for (int i = 1; i <= n; i++) {
            //cout << i << ": " << cnt[i] << endl;
            if (cnt[i] == 1) {
                q.push(i);
            }
        }
        set<pair<int,int>> bad;
        while (!q.empty()) {
            int i = q.front(); q.pop();
            //cout << i << endl;
            tri t = {-1,-1,-1,-1};
            for (tri j: tris[i]) {
                if (cnt[j.b] > 0 && cnt[j.c] > 0) {
                    t = j;
                    break;
                }
            }
            if (t.a == -1) continue;
            ord.push_back(t.id);
            //cout << "adding triangle " << t.id << endl;
            for (int j: {t.b,t.c}) {
                if (!bad.count({min(i,j),max(i,j)})) {
                    ans[i].push_back(j);
                    ans[j].push_back(i);
                    //cout << "found edge " << i << ' ' << j << endl;
                }
            }
            bad.insert({t.b,t.c});
            for (int j: {t.b,t.c}) {
                if (--cnt[j] == 1) {
                    q.push(j);
                }
            }
            --cnt[i];
        }
        vector<int> p;
        int cur = 1, prev = ans[1][0];
        while (true) {
            p.push_back(cur);
            assert(ans[cur].size() == 2);
            for (int j: ans[cur]) {
                if (j == prev) continue;
                prev = cur;
                cur = j;
                break;
            }
            if (cur == p[0]) break;
        }
        //output
        for (auto i: p) {
            cout << i << ' ';
        }
        cout << '\n';
        for (auto i: ord) {
            cout << i << ' ';
        }
        cout << '\n';
    }
}
