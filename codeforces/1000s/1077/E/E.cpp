#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5+5;
int n, a[maxn], c;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    map<int,int> freq;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        freq[ai]++;
    }
    for (auto& p: freq) {
        a[c++] = p.second;
    }
    sort(a,a+c);
    int ans = 0;
    for (int i = 1; i <= a[c-1]; i++) {
        int curr = i;
        int r = 0;
        for (int j = c-1; j >= 0 && a[j] >= curr; j--) {
            r += curr;        
            if (curr%2) break;
            curr /= 2;
        }
        ans = max(ans,r);
    }
    cout << ans << '\n';

    return 0;
}

