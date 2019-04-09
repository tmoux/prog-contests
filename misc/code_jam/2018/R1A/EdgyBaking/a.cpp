#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void ADD(vector<pair<double,double>>& v, pair<double,double> p) {
    for (auto q: v) {
        q.first += p.first;
        q.second += p.second;
    }
}

bool intersect(pair<double,double> a, pair<double,double> b) {
    if (a.first > b.first) swap(a,b);
    return (b.first <= a.second);
}

vector<pair<double,double>> MERGE(vector<pair<double,double>> v, vector<pair<double,double>> u) {
    vector<pair<double,double>> ret;
    for (auto p: v) ret.push_back(p);
    for (auto p: u) ret.push_back(u);
    sort(ret.begin(),ret.end(),[](auto a, auto b) {
            if (a.first != b.first) return a.first < b.first;
            return a.second < b.second;
            });
}

void solve(int qq) {
    int N; double P;
    cin >> N >> P;
    double perim = 0;
    vector<pair<double,double>> invls(N+1); //[l,r]
    for (int i = 0; i < N; i++) {
        int w, h; cin >> w >> h;
        P -= 2*(w+h);
        invls[i+1] = {2*min(w,h),2*sqrt(w*w+h*h)};
    }
    vector<vector<pair<double,double>>> ans(N+1);
    ans[0] = {0,0};
    for (int i = 1; i <= N; i++) {
        vector<pair<double,double>> b = ans[i-1];
        ADD(b,invls[i]);
        ans[i] = MERGE(b,ans[i-1]);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    cout << fixed << setprecision(10);
    for (int qq = 1; qq <= t; qq++) solve(qq);
}

