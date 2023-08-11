#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5+5;
int n;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    stack<int> a;
    vector<bool> used(n+1);
    vector<int> aa;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        aa.emplace_back(ai);
    }
    for (int i = n - 1; i >= 0; i--) {
        a.push(aa[i]);
    }
    for (int i = 0; i < n; i++) {
        int bi; cin >> bi;
        if (used[bi]) {
            cout << 0 << ' ';
            continue;
        }
        int r = 0;
        for (;;) {
            int t = a.top();
            a.pop();
            used[t] = true;
            r++;
            if (t == bi) break;
        }
        cout << r << ' ';
    }

    return 0;
}

