#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 5e5+5;
int n, Q, c[maxn], last[maxn], le[maxn], ri[maxn], st[maxn], en[maxn];
vector<int> q[maxn];

bool cleft(int i) {
    return st[i] > 1 && ri[st[i]-1] != -1 && ri[st[i]-1] <= en[i];
}

bool cright(int i) {
    return en[i] < n && le[en[i]] != -1 && le[en[i]] >= st[i];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 1; i < n; i++) cin >> c[i];
    for (int i = 1; i <= n; i++) {
        int x, y; cin >> x;
        while (x--) {
            cin >> y;
            q[i].push_back(y);
        }
    }
    memset(last,-1,sizeof(last));
    for (int i = 1; i < n; i++) {
        for (int j: q[i]) {
            last[j] = i;
        }
        le[i] = last[c[i]];
    }
    memset(last,-1,sizeof(last));
    for (int i = n - 1; i >= 1; i--) {
        for (int j: q[i+1]) {
            last[j] = i + 1;
        }
        ri[i] = last[c[i]];
    }
    for (int i = 1; i <= n; i++) {
        st[i] = en[i] = i;
        while (true) {
            if (cleft(i)) {
                en[i] = max(en[i],en[st[i]-1]);
                st[i] = min(st[i],st[st[i]-1]);
            }
            else if (cright(i)) ++en[i];
            else break;
        }
    }
    cin >> Q;
    while (Q--) {
        int a, b; cin >> a >> b;
        cout << (st[a] <= b && b <= en[a] ? "YES" : "NO") << '\n';
    }    
}

