#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1e9+7;
const int N = 2005;
int n, m;
char grid[N][N];

void madd(int& a, int b) {
    a += b;
    if (a > M) a -= M;
}

int mult(int a, int b) {
    return (1LL*a*b) % M;
}

struct LazySeg
{
    int sz, *sum, *lazy;
    LazySeg() {}
    LazySeg(int _n) {
        sz = _n;
        sum = new int[4*sz+3];
        lazy = new int[4*sz+3];
        build(1,1,sz);
    }
    void build(int i, int a, int b) {
        if (a > b) return;
        sum[i] = 0;
        lazy[i] = 0;
        if (a == b) {
            return;
        }
        build(i*2,a,(a+b)/2);
        build(i*2+1,(a+b)/2+1,b);
    }

    void push(int i, int a, int b) {
        if (a != b) {
            int m = (a+b)/2;
            madd(lazy[i*2],lazy[i]);
            madd(sum[i*2],mult(m-a+1,lazy[i]));

            madd(lazy[i*2+1],lazy[i]);
            madd(sum[i*2+1],mult(b-m,lazy[i]));

        }
        lazy[i] = 0;
    }

    void _add(int i, int a, int b, int st, int en, int x) {
        //lazy: already accounted for in your node, not the children
        if (st <= a && b <= en) {
            madd(lazy[i],x);
            madd(sum[i],mult(b-a+1,x));
            return;
        }
        push(i,a,b);
        int m = (a+b)/2;
        if (st <= m) {
            _add(i*2,a,m,st,en,x);
        }
        if (en > m) {
            _add(i*2+1,m+1,b,st,en,x);
        }
        sum[i] = sum[i*2];
        madd(sum[i],sum[i*2+1]);
    }

    void add(int st, int en, int x) {
        _add(1,1,sz,st,en,x);
    }

    int _getsum(int i, int a, int b, int st, int en) {
        push(i,a,b);
        if (st <= a && b <= en) {
            return sum[i];
        }
        int ret = 0;
        int m = (a+b)/2;
        if (st <= m) {
            madd(ret,_getsum(i*2,a,m,st,en));
        }
        if (en > m) {
            madd(ret,_getsum(i*2+1,m+1,b,st,en));
        }
        return ret;
    }

    int getsum(int st, int en) {
        return _getsum(1,1,sz,st,en);    
    }
};

LazySeg dDown[N], dRight[N];

int rowSfx[N][N], colSfx[N][N];

int main() {
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> grid[i][j];
        }
    }
    if (n == 1 && m == 1) {
        cout << 1 << '\n';
        return 0;
    }
    for (int i = 1; i <= m; i++) {
        dDown[i] = LazySeg(n);
    }
    for (int i = 1; i <= n; i++) {
        dRight[i] = LazySeg(m);
    }
    dDown[1].add(1,1,1);
    dRight[1].add(1,1,1);
    for (int i = n; i >= 1; i--) {
        for (int j = m; j >= 1; j--) {
            rowSfx[i][j] = grid[i][j] == 'R';
            rowSfx[i][j] += rowSfx[i][j+1];

            colSfx[i][j] = grid[i][j] == 'R';
            colSfx[i][j] += colSfx[i+1][j];
        }
    }
    for (int k = 2; k <= n+m; k++) {
        for (int i = 1, j = k-i; i <= n && j >= 1; i++,j--) {
            if (j > m) continue;
            //cout << i << ' ' << j << endl;
            //continue;
    //for (int i = 1; i <= n; i++) {
        //for (int j = 1; j <= m; j++) {
            //update dp
            /*
            if (i > 1 && j > 1) {
                if (i <= n-colSfx[i][j]) {
                    int addDown = dDown[j]->getsum(i-1,i-1);
                    dDown[j]->add(i,i,addDown);
                }
                if (j <= m-rowSfx[i][j]) {
                    int addRight = dRight[i]->getsum(j-1,j-1);
                    dRight[i]->add(j,j,addRight);
                }
            }
            */
            int l = j + 1;
            int r = m-rowSfx[i][j+1];
            int dp = dDown[j].getsum(i,i);
            if (l <= r) dRight[i].add(l,r,dp);
            //cout << "down " << i << ' ' << j << ": " << dp << '\n';

            l = i + 1;
            r = n-colSfx[i+1][j];
            dp = dRight[i].getsum(j,j);
            if (l <= r) dDown[j].add(l,r,dp);
            //cout << "right " << i << ' ' << j << ": " << dp << '\n';
        }
    }

    int ans = dDown[m].getsum(n,n);
    madd(ans,dRight[n].getsum(m,m));
    cout << ans << '\n';
}

