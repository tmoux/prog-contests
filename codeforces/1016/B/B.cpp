#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

string s, t;
int n, m, q, pre[1005];

int query(int l, int r) {
    r = r - t.size() + 1;
    if (r < l) return 0;
    return pre[r] - pre[l-1];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> q;
    cin >> s >> t;
    for (int i = 0; i < s.size(); i++) {
        if (s.substr(i,t.size()) == t) {
            pre[i+1] = 1;
        }
        pre[i+1] += pre[i];
    }

    while (q--) {
        int l, r; cin >> l >> r;
        cout << query(l,r) << '\n';
    }

    return 0;
}
	

