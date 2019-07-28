#include <bits/stdc++.h>
using namespace std;
using ll = long long;


const int maxn = 2e5+5;
int a[maxn], pre[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int q; cin >> q;
    while (q--) {
        int n, k; cin >> n >> k;
        int oneCount = 0;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            a[i] %= 2;
            if (a[i] == 1) oneCount++;
        }
        if (oneCount < k || oneCount % 2 != k % 2) {
            cout << "NO\n";
        }
        else {
            vector<pair<int,int>> ans;
            int last = 0;
            while (k) {
                if (k == 1) {
                    ans.push_back({last+1,n});
                    k--;
                }
                else {
                    for (int i = last+1; i <= n; i++) {
                        if (a[i] == 1) {
                            ans.push_back({last+1,i});
                            last = i;
                            k--;
                            break;
                        }
                    }
                }
            }
            cout << "YES\n";
            for (auto p: ans) {
                cout << p.second << ' ';
            }
            cout << '\n';
        }
    }

}

