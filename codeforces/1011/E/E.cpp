#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 100005;
int n, k, A[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    int gc = k;
    for (int i = 0; i < n; i++) {
        gc = __gcd(gc,A[i]);
    }
    vector<int> ans;
    int cop = gc;
    while (cop <= k) {
        ans.push_back(cop%k);
        cop += gc;
    }
    sort(ans.begin(),ans.end());
    cout << ans.size() << '\n';
    for (int i: ans) {
        cout << i << ' ';
    }

    return 0;
}
	

