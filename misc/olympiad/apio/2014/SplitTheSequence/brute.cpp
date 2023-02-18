#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1005, maxk = 205;
int N, K, a[maxn];

ll pre[maxn];
ll dp[maxn][maxk];
int previous[maxn][maxk];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> K;
    for (int i = 1; i <= N; i++) {
        cin >> a[i];
        pre[i] = a[i] + pre[i-1];
    }
    for (int i = 1; i <= N; i++) {
        for (int k = 1; k <= K; k++) {
            pair<ll,int> best = {0,0};
            for (int j = 1; j < i; j++) {
                //cout << i << ' ' << k << ' ' << j << endl;
                best = max(best,{dp[j][k-1]+(pre[i]-pre[j])*(pre[j]),j});
            }
            dp[i][k] = best.first;
            previous[i][k] = best.second;
            printf("[%d][%d]: %d\n",i,k,dp[i][k]);
        }
    }
    //output
    cout << dp[N][K]<< '\n';
    int curr = N;
    int k = K;
    vector<int> ans;
    while (k > 0) {
        curr = previous[curr][k];
        k--;
        ans.push_back(curr);
    }
    reverse(ans.begin(),ans.end());
    for (int i: ans) {
        cout << i << ' ';
    }
    cout << '\n';
}


