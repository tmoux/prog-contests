#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5, M = 1e9+7;
void madd(int& a, int b) {
    a += b;
    if (a >= M) a -= M;
}
int ex2[maxn];
int N;
int a[2*maxn];

int main()
{
    freopen("help.in","r",stdin); freopen("help.out","w",stdout);
    cin >> N;
    ex2[0] = 1;
    for (int i = 1; i <= N; i++) {
        int l, r; cin >> l >> r;
        a[l] = i;
        a[r] = -i;
        ex2[i] = (ex2[i-1]*2) % M;
    }
    int ans = 0;
    int active = 0;
    for (int i = 1; i <= 2*N; i++) {
        if (a[i] > 0) {
            madd(ans,ex2[N-1-active]);
            active++;
        }
        else {
            active--;
        }
    }
    cout << ans << '\n';
}
