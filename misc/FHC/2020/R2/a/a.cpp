#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    int N, K; cin >> N >> K;
    vector<ll> S(N);
    for (int i = 0; i < K; i++) {
        cin >> S[i];
    }
    ll As, Bs, Cs, Ds; cin >> As >> Bs >> Cs >> Ds;
    vector<ll> X(N);
    for (int i = 0; i < K; i++) {
        cin >> X[i];
    }
    ll Ax, Bx, Cx, Dx; cin >> Ax >> Bx >> Cx >> Dx;
    vector<ll> Y(N);
    for (int i = 0; i < K; i++) {
        cin >> Y[i];
    }
    ll Ay, By, Cy, Dy; cin >> Ay >> By >> Cy >> Dy;
    for (int i = K; i < N; i++) {
        S[i] = (As*S[i-2]+Bs*S[i-1]+Cs)%Ds;
        X[i] = (Ax*X[i-2]+Bx*X[i-1]+Cx)%Dx;
        Y[i] = (Ay*Y[i-2]+By*Y[i-1]+Cy)%Dy;
    }
    ll need = 0, excess = 0;
    for (int i = 0; i < N; i++) {
        if (S[i] < X[i]) {
            need += X[i]-S[i];
        }
        else if (S[i] > X[i]+Y[i]) {
            excess += S[i]-(X[i]+Y[i]);
        }
    }
    ll mn = min(need,excess);
    need -= mn;
    excess -= mn;
    ll ans = mn;
    bool poss = true;
    if (need > 0) {
        ll cnt = 0;
        for (int i = 0; i < N; i++) {
            if (S[i] >= X[i]) {
                cnt += min(S[i],X[i]+Y[i])-X[i];
            }
        }
        if (cnt < need) {
            poss = false;
        }
        else {
            ans += need;
        }
    }
    else if (excess > 0) {
        ll cnt = 0;
        for (int i = 0; i < N; i++) {
            if (S[i] <= X[i]+Y[i]) {
                cnt += X[i]+Y[i]-max(S[i],X[i]);
            }
        }
        if (cnt < excess) {
            poss = false;
        }
        else {
            ans += excess;
        }
    }
    if (!poss) {
        cout << -1 << '\n';
    }
    else {
        cout << ans << '\n';
    }
    /*
    for (auto i: S) {
        cout << i << ' ';
    }
    cout << '\n';
    for (auto i: X) {
        cout << i << ' ';
    }
    cout << '\n';
    for (auto i: Y) {
        cout << i << ' ';
    }
    cout << '\n';
    */
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
}

