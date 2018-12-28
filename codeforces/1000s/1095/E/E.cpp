#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e6+6;
int n, pre[maxn];

struct Sparse
{
    //sparse table data structure for max
    static const int mk = 21; //change this number based on bounds
    int* tb[mk];
    static inline int lg(int x) { return 32 - __builtin_clz(x) - 1; }
    Sparse(int *a, int n) {
        for (int i = 0; i < mk; i++) {
            tb[i] = new int[n+1];
        }
        for (int i = 1; i <= n; i++) tb[0][i] = a[i];
        for (int k = 1; k <= lg(n); k++) {
            for (int i = 1; i <= n; i++) {
                int nx = i + (1<<(k-1));
                if (nx <= n) tb[k][i] = min(tb[k-1][i],tb[k-1][nx]);
                else tb[k][i] = tb[k-1][i];
            }
        }
    }
    int getmin(int l, int r) {
        if (l > r) return 999999;
        int g = lg(r-l+1);
        return min(tb[g][l],tb[g][r-(1<<g)+1]);
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    string s; cin >> s;
    for (int i = 1; i <= n; i++) {
        pre[i] = s[i-1] == '(' ? 1 : -1;
        pre[i] += pre[i-1];
    }
    Sparse *sp = new Sparse(pre,n);
    if (pre[n] == 2) {
        //change ( to a )
        int cnt = 0;
        for (int i = 1; i <= n; i++) {
            if (s[i-1] == '(' && sp->getmin(1,i-1) >= 0 && sp->getmin(i,n) >= 2) cnt++;
        }
        cout << cnt << '\n';
    }
    else if (pre[n] == -2) {
        //change ) to a (
        int cnt = 0;
        for (int i = 1; i <= n; i++) {
            if (s[i-1] == ')' && sp->getmin(1,i-1) >= 0 && sp->getmin(i,n) >= -2) cnt++; 
        }
        cout << cnt << '\n';
    }
    else {
        cout << 0 << '\n';
        //never possible
    }

    return 0;
}

