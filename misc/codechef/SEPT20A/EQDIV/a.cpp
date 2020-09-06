#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int K;
ll calc(int x) {
    ll r = 1;
    for (int i = 0; i < K; i++) {
        r *= x;
    }
    return r;
}
void brute(int N) {
    pair<ll,vector<string>> best = {1e9,{}};
    for (int i = 0; i < (1<<N); i++) {
        ll pa = 0, pb = 0;
        string s = "";
        for (int j = 0; j < N; j++) {
            if (i & (1<<j)) {
                pa += calc(j+1);
                s += '0';
            }
            else {
                pb += calc(j+1);
                s += '1';
            }
        }
        if (best.first > abs(pa-pb)) {
            best = {abs(pa-pb),{s}};
        }
        else if (best.first == abs(pa-pb)) {
            best.second.push_back(s);
        }
    }
    cout << best.first << '\n';
    cout << "sz = " << (best.second.size()) << endl;
    cout << fixed << setprecision(6) << (best.second.size()/pow(2,N)) << endl;
    /*
    for (auto s: best.second) {
        cout << s << '\n';
    }
    */
}

void greedy(int N) {
    ll tot = 0;
    for (int i = 1; i <= N; i++) {
        tot += calc(i);
    }
    ll target = tot/2;
    ll pa = 0;
    string s = "";
    for (int i = N; i >= 1; i--) {
        if (pa + calc(i) <= target) {
            pa += calc(i);
            s += '1';
        }
        else {
            s += '0';
        }
    }
    reverse(s.begin(),s.end());
    cout << abs(pa-(tot-pa)) << '\n';
    cout << s << '\n';
}

void solve(int N) {
    //subtask 1
    if (K == 1) {
        if (N % 4 == 0) {
            cout << 0 << '\n';
            for (int i = 0; i < N; i++) {
                cout << (i%4==0||i%4==3);
            }
            cout << '\n';
        }
        else if (N % 4 == 1) {
            cout << 1 << '\n';
            cout << "1";
            for (int i = 1; i < N; i++) {
                cout << ((i-1)%4==0||(i-1)%4==3);
            }
            cout << '\n';
        }
        else if (N % 4 == 2) {
            cout << 1 << '\n';
            cout << "10";
            for (int i = 2; i < N; i++) {
                cout << ((i-2)%4==0||(i-2)%4==3);
            }
            cout << '\n';
        }
        else if (N % 4 == 3) {
            cout << 0 << '\n';
            cout << "110";
            for (int i = 3; i < N; i++) {
                cout << ((i-3)%4==0||(i-3)%4==3);
            }
            cout << '\n';
        }
    }
    else assert(false);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> K;
    int t; cin >> t;
    while (t--) {
        int N; cin >> N;
        //solve(N);
        //cout << "n = " << N << endl;
        brute(N);
        //greedy(N);
    }
}
