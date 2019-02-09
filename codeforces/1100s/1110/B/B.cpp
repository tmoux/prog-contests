#include <bits/stdc++.h>
using namespace std;
using ll = long long;


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m, k; cin >> n >> m >> k;
    vector<int> b(n);
    vector<int> gaps;
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        if (i > 0) gaps.push_back(b[i]-b[i-1]-1);
    }
    sort(gaps.begin(),gaps.end(),greater<int>());
    int ans = b[n-1] - b[0] + 1;
    int cnt = 1;
    int ptr = 0;
    while (cnt < k) {
        cnt++;
        ans -= gaps[ptr++];
    }
    cout << ans << '\n';

    return 0;
}

