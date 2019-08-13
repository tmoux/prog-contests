#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int N, K;

struct Rect
{
    int x1, y1, x2, y2;
};
vector<Rect> recs;

bool isWhite(int r, int c, int sz) {
    r /= sz;
    c /= sz;
    return (r+c) % 2 == 0;
}

ll solve(int sz) {
    ll res = 0;
    ll num = N/sz;
    if (num % 2 == 0) {
        res = 1LL*N*N/2;
    }
    else {
        res = (1LL*sz*sz) * (1LL*N*N) / 2;
    }
    //cout << sz << ": " << res << '\n';
    for (Rect re: recs) {
        for (int r = re.x1; r <= re.x2; r++) {
            for (int c = re.y1; c <= re.y2; c++) {
                if (isWhite(r,c,sz)) res++;
                else res--;
            }
        }
    }
    return res;
}

ll solve2(int sz) {
    ll res = 0;
    ll num = N/sz;
    if (num % 2 == 0) {
        res = 1LL*N*N/2;
    }
    else {
        res = (1LL*sz*sz) * (1LL*N*N+1) / 2;
    }
    for (Rect re: recs) {
        for (int r = re.x1; r <= re.x1; r++) {
            for (int c = re.y1; c <= re.y2; c++) {
                if (!isWhite(r,c,sz)) res++;
                else res--;
            }
        }
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> K;
    for (int i = 0; i < K; i++) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        x1--;
        y1--;
        x2--;
        y2--;
        recs.push_back({x1,y1,x2,y2});
    }
    ll ans = 1LL*N*N;
    for (int sz = 1; sz < N; sz++) {
        if (N % sz == 0) {
            ans = min(ans,solve(sz));
            ans = min(ans,solve2(sz));
        }
    }
    cout << ans << '\n';
}

