#include <bits/stdc++.h>
using namespace std;
using ll = long long;

string s;

map<char,int> dx = {
              {'W',0},
              {'A',-1},
              {'S',0},
              {'D',1},
};

map<char,int> dy = {
              {'W',1},
              {'A',0},
              {'S',-1},
              {'D',0},
};

int pre[maxn];

bool check(int mx, int mn, int pt) {
    int mnIndex = -1;
    for (int i = 1; i < pt; i++) {
        if (pre[i] == mn) {
            mnIndex = i;
            break;
        }
    }
    int mxIndex = -1;
    for (int i = pt-1; i >= 1; i--) {
        if (pre[i] == mx) {
            mxIndex = i;
            break;
        }
    }
    assert(mnIndex != 1 && mxIndex != 1);
    return mxIndex < mnIndex;
}

void solve() {
    int n = s.size();    
    for (int i = 0; i <= n; i++) {
        pre[i] = 0;
    }
    int mx = 0, mn = 0;
    int pt = 1;
    for (char c: s) {
        if (c == 'A' || c == 'D') continue;
        if (c == 'W') {
            pre[pt] = pre[pt-1] + 1;
            pt++;
        }
        else {
            pre[pt] = pre[pt-1] - 1;
            pt++;
        }
        mx = max(mx,pre[pt-1]);
        mn = min(mn,pre[pt-1]);
    }
    int height = mx-mn+1;
    bool canReduceHeight = check(mx,mn,pt);
    for (int i = 1; i < pt; i++) {
        pre[i] *= -1;
    }
    canReduceHeight |= check(-mn,-mx,pt);

    for (int i = 0; i <= n; i++) {
        pre[i] = 0;
    }
    mx = 0, mn = 0;
    pt = 1;
    for (char c: s) {
        if (c == 'W' || c == 'S') continue;
        if (c == 'D') {
            pre[pt] = pre[pt-1] + 1;
            pt++;
        }
        else {
            pre[pt] = pre[pt-1] - 1;
            pt++;
        }
        mx = max(mx,pre[pt-1]);
        mn = min(mn,pre[pt-1]);
    }
    int width = mx-mn+1;
    bool canReduceWidth = check(mx,mn,pt);
    for (int i = 1; i < pt; i++) {
        pre[i] *= -1;
    }
    canReduceWidth |= check(-mn,-mx,pt);   

}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        cin >> s;
        solve();
    }
}

