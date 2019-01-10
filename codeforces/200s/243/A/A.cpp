#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5, maxk = 21;
int n, a[maxn], nxt[maxk][maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int k = 0; k < maxk; k++) {
        for (int i = n - 1; i >= 0; i--) {
            if (i == n - 1) nxt[k][i] = (a[i] & (1<<k)) ? i : n;    
            else nxt[k][i] = (a[i] & (1<<k)) ? i: nxt[k][i+1];
        }
    }
    vector<int> ans;
    ans.reserve(maxn*maxk);
    for (int i = 0; i < n; i++) {
        int curr = a[i];
        int currIdx = i;
        while (true) {
            ans.push_back(curr);
            int mnNext = n;
            for (int k = 0; k < maxk; k++) {
                if (!(curr & (1<<k))) {
                    mnNext = min(mnNext,nxt[k][currIdx]); 
                }
            }
            currIdx = mnNext;
            if (currIdx == n) break;
            curr |= a[currIdx];    
        }
    }
    sort(ans.begin(),ans.end());
    ans.erase(unique(ans.begin(),ans.end()),ans.end());
    cout << ans.size() << '\n';

    return 0;
}

