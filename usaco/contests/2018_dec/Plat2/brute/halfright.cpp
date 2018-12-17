#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int N, K, a[maxn];
set<int> len[maxn];
int pre[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("itout.in","r",stdin); freopen("itout.out","w",stdout);
    cin >> N >> K;
    for (int i = 0; i < N; i++) cin >> a[i];
    vector<int> T(N+1);
    fill(T.begin(),T.end(),maxn);
    T[0] = 0;
    int ans = 0, last = 0;
    for (int i = 0; i < N; i++) {
        auto it = lower_bound(T.begin(),T.end(),a[i]);
        int dist = (int)distance(T.begin(),it);
        if (dist > ans) {
            ans = dist;
            last = a[i];
        }
        else if (dist == ans) {
            last = max(last,a[i]);
        }
        *it = a[i]; 
        //take largest previous one
        len[dist].insert(a[i]);
        if (len[dist-1].empty()) {
            pre[a[i]] = 0;
            continue;
        }
        auto itr = len[dist-1].lower_bound(a[i]);
        /*
        cout << a[i] << ' ' << dist << ":\n";
        for (int a: len[dist-1]) {
            cout << a << ' ';
        }
        cout << '\n';
        */
        if (itr == len[dist-1].begin()) {
            pre[a[i]] = 0;    
        }
        else {
            --itr;
            pre[a[i]] = *itr;
        }
    }
    //cout << last << '\n';
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

    return 0;
}

