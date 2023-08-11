#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
vector<int> sub[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int si, ri; cin >> si >> ri;
        sub[si].push_back(ri);
    }
    set<int> active;
    for (int i = 1; i <= m; i++) {
        sort(sub[i].begin(),sub[i].end(),greater<int>());
        if (sub[i].empty() || sub[i][0] <= 0) continue;
        for (int j = 1; j < sub[i].size(); j++) {
            sub[i][j] += sub[i][j-1];
        }
        if (!sub[i].empty()) active.insert(i);
    }

    /*
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j < sub[i].size(); j++) {
            cout << sub[i][j] << ' ';
        }
        cout << '\n';
    }
    */
    int maxans = 0;
    for (int i = 1; i <= n; i++) {
        int curr = 0;
        int counted = 0;
        for (int a: active) {
            if (sub[a][i-1] > 0) {
                curr += sub[a][i-1];
                counted++;
            }
        }
        maxans = max(maxans,curr);
        //cout << i << ": " << curr << '\n';
        vector<int> removes;
        for (int a: active) {
            if (sub[a].size() == i) removes.push_back(a);    
        }
        for (int a: removes) active.erase(a);
    }

    cout << maxans << '\n';

    return 0;
}

