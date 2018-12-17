#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int N, a[maxn], pre[maxn];

double getAvg(int l, int r) {
    int n = r-l+1;
    return (pre[N]-(pre[r]-pre[l-1]))/(double)(N-n);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //freopen("sabotage.in","r",stdin); freopen("sabotage.out","w",stdout);
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> a[i];
        pre[i] = a[i];
        pre[i] += pre[i-1];
    }
    double ans = 1e30;
    for (int l = 2; l <= N - 1; l++) {
        cout << l << ": ";
        for (int j = l; j <= N - 1; j++) {
            cout << getAvg(l-1,j) << ' ';
        }
        cout << '\n';
    }
    cout << ans << '\n';


    return 0;
}

