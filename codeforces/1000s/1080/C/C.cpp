#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll checker(ll x1, ll x2, ll y1, ll y2, bool white) {
    ll w1 = ((y2-y1+1)%2==1 ? (y2-y1):(y2-y1+1)) * (x2-x1+1)/2;
    if ((y2-y1+1)%2 == 1) {
        if ((x2-x1+1)%2 == 0) {
            w1 += (x2-x1+1)/2;
        }
        else {
            if (x2 % 2 == y2 % 2) {
                w1 += (x2-x1+1)/2+1;
            }
            else {
                w1 += (x2-x1+1)/2;
            }
        }
    }
    if (white) return w1;
    else return ((x2-x1+1)*(y2-y1+1))-w1;
}

void solve() {
    ll n, m; cin >> n >> m;
    ll x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
    ll x3, y3, x4, y4; cin >> x3 >> y3 >> x4 >> y4;
    bool unfair = n%2==1 && m%2 == 1;
    ll white = unfair ? 1LL*n*m/2+1 : 1LL*n*m/2;
    ll black = 1LL*n*m/2;
    ll ax1 = max(x1,x3);
    ll ax2 = min(x2,x4);
    ll ay1 = max(y1,y3);
    ll ay2 = min(y2,y4);
    //cout << ax1 << ' ' << ax2 << ' ' << ay1 << ' ' << ay2 << '\n';
    ll w1, b1;
    if (ax2 < ax1 || ay2 < ay1) {
        w1 = checker(x1,x2,y1,y2,0);
        b1 = checker(x3,x4,y3,y4,1);
        white += w1;
        black -= w1;
        white -= b1;
        black += b1;
    }
    else {
        ll interWhite = checker(ax1,ax2,ay1,ay2,1);
        ll interBlack = checker(ax1,ax2,ay1,ay2,0);
        w1 = checker(x1,x2,y1,y2,1);
        ll r1b = checker(x1,x2,y1,y2,0);
        b1 = checker(x3,x4,y3,y4,0);
        ll r2w = checker(x3,x4,y3,y4,1);
        white -= (w1+r2w-interWhite);
        black -= (b1+r1b-interBlack);
        //cout << white << ' ' << black << '\n';
        white += ((x2-x1+1)*(y2-y1+1))-((ax2-ax1+1)*(ay2-ay1+1));
        black += ((x4-x3+1)*(y4-y3+1));
    }
    cout << white << ' ' << black << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();

    return 0;
}

