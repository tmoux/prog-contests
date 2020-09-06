#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//remove 1 big edge, remove 1 edge from each circle
//OR
//keep all big edges, remove 1 edge from each circle, 
//plus pick one circle where you can remove 2 edges from the 2 "sides"
//2nd: maintain sum of max edge of all circles, plus biggest edge in the other "side"

const ll MOD = 1e9+7;

void solve() {
    int N, M, E, K; cin >> N >> M >> E >> K;
    vector<ll> X(N), Y(N), I(E), W(E);
    for (int i = 0; i < K; i++) cin >> X[i];
    int Ax, Bx, Cx; cin >> Ax >> Bx >> Cx;
    for (int i = 0; i < K; i++) cin >> Y[i];
    int Ay, By, Cy; cin >> Ay >> By >> Cy;
    for (int i = 0; i < K; i++) cin >> I[i];
    int Ai, Bi, Ci; cin >> Ai >> Bi >> Ci;
    for (int i = 0; i < K; i++) cin >> W[i];
    int Aw, Bw, Cw; cin >> Aw >> Bw >> Cw;
    for (int i = K; i < N; i++) {
        X[i] = (Ax*X[i-2]+Bx*X[i-1]+Cx)%M;
        Y[i] = (Ay*Y[i-2]+By*Y[i-1]+Cy)%M;
    }
    for (int i = 0; i < N; i++) {
        if (X[i] > Y[i]) swap(X[i],Y[i]);
    }
    for (int i = K; i < E; i++) {
        I[i] = (Ai*I[i-2]+Bi*I[i-1]+Ci)%(N*M+N);
        W[i] = (Aw*W[i-2]+Bw*W[i-1]+Cw)%(1000000000);
    }
    vector<ll> ans1(E), ans2(E);
    //compute ans1
    vector<ll> weight(N*M+N,1);
    vector<multiset<ll>> circles(N);
    multiset<ll> bigs;
    for (int i = 0; i < N; i++) {
        bigs.insert(1);    
        for (int j = 0; j < M; j++) {
            circles[i].insert(1);
        }
    }
    ll total = N*M+N;
    ll cur = N+1;
    //ans2
    vector<vector<multiset<ll>>> ms(N,vector<multiset<ll>>(2));
    bool is = false;
    multiset<ll> mx2;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (X[i] <= j && j < Y[i]) {
                ms[i][0].insert(1);
            }
            else {
                ms[i][1].insert(1);
            }
        }
        if (!ms[i][0].empty() && !ms[i][1].empty()) {
            mx2.insert(1);
            is = true;
        }
    }
    auto getPair = [&ms](int i) {
        vector<ll> v;
        if (!ms[i][0].empty()) v.push_back(*ms[i][0].rbegin());
        if (!ms[i][1].empty()) v.push_back(*ms[i][1].rbegin());
        if (v.size() == 1) {
            return make_pair(v[0],-1LL);
        }
        else if (v.size() == 2) {
            if (v[1] > v[0]) swap(v[0],v[1]);
            return make_pair(v[0],v[1]);
        }
        else assert(false);
    };
    ll cur2 = is?N+1:N;
    for (int i = 0; i < E; i++) {
        int id = I[i]/M;
        ll orig = weight[I[i]];
        if (id < N) {
            cur -= *circles[id].rbegin();
            auto it = circles[id].find(weight[I[i]]);
            circles[id].erase(it);
            total -= weight[I[i]];

            weight[I[i]] = W[i];

            total += weight[I[i]];
            circles[id].insert(weight[I[i]]);
            cur += *circles[id].rbegin();
        }
        else {
            cur -= *bigs.rbegin();
            auto it = bigs.find(weight[I[i]]);
            bigs.erase(it);
            total -= weight[I[i]];

            weight[I[i]] = W[i];

            total += weight[I[i]];
            bigs.insert(weight[I[i]]);
            cur += *bigs.rbegin();
        }
        ans1[i] = total - cur;
        //ans2
        if (id < N) {
            cur2 -= (mx2.empty()) ? 0 : *mx2.rbegin();
            pair<ll,ll> p = getPair(id);
            cur2 -= p.first;
            if (p.second != -1) {
                auto it = mx2.find(p.second);
                mx2.erase(it);
            }

            int which = I[i]%M;
            if (X[id] <= which && which < Y[id]) {
                auto it = ms[id][0].find(orig);    
                ms[id][0].erase(it);
                ms[id][0].insert(W[i]);
            }
            else {
                auto it = ms[id][1].find(orig);    
                ms[id][1].erase(it);
                ms[id][1].insert(W[i]);
            }

            p = getPair(id);
            cur2 += p.first;
            if (p.second != -1) {
                mx2.insert(p.second);
            }
            cur2 += (mx2.empty()) ? 0 : *mx2.rbegin();
        }
        ans2[i] = total - cur2;

        //cout << i << ": " << min(ans1[i],ans2[i]) << '\n';
    }
    ll prod = 1;
    for (int i = 0; i < E; i++) {
        prod = (prod*(min(ans1[i],ans2[i])%MOD))%MOD;
    }
    cout << prod << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
}

