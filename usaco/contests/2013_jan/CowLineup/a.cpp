#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int N, K, a[maxn];
int maxIndex[maxn]; //largest index for i where no more than K+1 breeds are used
map<int,vector<int>> indices;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("lineup.in","r",stdin); freopen("lineup.out","w",stdout);
    cin >> N >> K;
    for (int i = 1; i <= N; i++) {
        cin >> a[i];
        indices[a[i]].push_back(i);
    }
    map<int,int> mp;
    int R = 0;
    for (int L = 1; L < N-K; L++) {
        while (mp.size() <= K + 1) {
            if (R + 1 > N) break;
            mp[a[++R]]++;
        }
        maxIndex[L] = R - 1;
        /*
        for (auto p: mp) {
            cout << p.first << ' ' << p.second << '\n';
        }
        */
        //remove last index
        if (--mp[a[L]] == 0) mp.erase(a[L]);
    }
    for (int i = N-K; i <= N; i++) maxIndex[i] = N;
    int ans = 0;
    for (int i = 1; i <= N; i++) {
        vector<int>& v = indices[a[i]];
        auto it = upper_bound(v.begin(),v.end(),maxIndex[i]);
        assert(it != v.begin());
        --it;
        auto it2 = lower_bound(v.begin(),v.end(),i);
        ans = max(ans,(int)distance(it2,it)+1);
    }
    cout << ans << '\n';

    return 0;
}

