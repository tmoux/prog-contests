#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 5005;
int n, k;
int a[maxn];
set<int> nums[maxn];
int ans[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    bool poss = true;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        //find a color to assign
        bool found = false;
        for (int j = 1; j <= k; j++) {
            if (nums[j].empty()) {
                ans[i] = j;
                nums[j].insert(a[j]);
                found = true;
                break;
            }
        }
        if (!found) {
            for (int j = 1; j <= k; j++) {
                bool canWork = true;
                if (nums[j].count(a[i])) canWork = false;
                if (canWork) {
                    ans[i] = j;
                    nums[j].insert(a[i]);
                    break;
                }
            }
            if (ans[i] == 0) {
                poss = false;
                break;
            }
        }
    }

    if (poss) {
        cout << "YES\n";
        for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
        cout << '\n';
    }
    else {
        cout << "NO\n";
    }
    
    return 0;
}

