#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int N, K, a[maxn], pre[maxn];

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    //freopen("itout.in","r",stdin); freopen("itout.out","w",stdout);
    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }
    //Longest increasing subsequence???
    vector<int> T(N+1);
    fill(T.begin(),T.end(),maxn);
    T[0] = 0;
    int ans = 0, last = 0;
    for (int i = 0; i < N; i++) {
        auto it = lower_bound(T.begin(),T.end(),a[i]);
        *it = a[i]; 
        int dist = (int)distance(T.begin(),it);
        if (dist > ans) {
            ans = dist;
            last = a[i];
        }
        pre[a[i]] = T[dist-1];
    }
    vector<bool> used(N+1,false);
    while (last != 0) {
        used[last] = true;
        last = pre[last];    
    }
    vector<int> res;
    for (int i = 1; i <= N; i++) {
        if (!used[i]) res.push_back(i);
    }
    //output
    cout << res.size() << '\n';
    for (int i: res) {
        cout << i << '\n';
    }
    /*
    for (int i = 1; i <= N; i++) {
        printf("%d: %d\n",i,pre[i]);
    }
    cout << last << '\n';
    */


    return 0;
}

