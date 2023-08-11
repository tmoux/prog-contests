#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e6+6;
int n, A[maxn];
int freq[10005];
double sqr(double d) {
    return d*d;
}

void solve() {
    scanf("%d",&n);
    memset(freq,0,sizeof(freq));
    vector<int> vs;
    for (int i = 0; i < n; i++) {
        scanf("%d",A+i);
        freq[A[i]]++;
        if (freq[A[i]] == 2 || freq[A[i]] == 4) vs.push_back(A[i]);
    }
    sort(vs.begin(),vs.end());
    double mx = 1e18;
    pair<int,int> ans;
    for (int i = 0; i < vs.size() - 1; i++) {
        double tr = sqr((2*(vs[i]+vs[i+1])))/((double)(vs[i])*vs[i+1]);
        //cout << vs[i] << ' ' << vs[i+1] << ' ' << tr << '\n';
        if (tr < mx) {
            mx = tr;
            ans = {vs[i],vs[i+1]};
        }
    }
    printf("%d %d %d %d\n",ans.first,ans.first,ans.second,ans.second);
}

int main()
{
    int t; scanf("%d",&t);
    while(t--) solve();

    return 0;
}
	

