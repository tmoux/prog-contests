#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1005;
int n, a[maxn], diff[maxn];

bool valid(int x) {
    for (int i = 1; i <= x; i++) {
        int f = diff[i];
        bool allsame = true;
        for (int j = i + x; j <= n; j += x) {
            if (diff[j] != f) {
                allsame = false;
                break;
            }
        }
        if (!allsame) return false;
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        diff[i] = a[i] - a[i-1];
    }
    vector<int> ans;
    for (int i = 1; i <= n; i++) {
        if (valid(i)) {
            ans.push_back(i);    
        }
    }
    cout << ans.size() << '\n';
    for (int j: ans) {
        cout << j << ' ';
    }


    return 0;
}

