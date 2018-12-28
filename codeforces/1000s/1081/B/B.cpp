#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int a[maxn];
vector<int> those[maxn];
int ans[maxn];
int idx = 1;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    int total = n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] = n-a[i];
        those[a[i]].push_back(i);
        if (those[a[i]].size() == a[i]) {
            //fill them in
            for (int a: those[a[i]]) {
                ans[a] = idx;
            }
            idx++;
            total -= a[i];
            those[a[i]].clear();
        }
    }

    if (total != 0) {
        cout << "Impossible\n";
    }
    else {
        cout << "Possible\n";
        for (int i = 1; i <= n; i++) {
            cout << ans[i] << ' ';
        }
        cout << '\n';
    }

    return 0;
}

