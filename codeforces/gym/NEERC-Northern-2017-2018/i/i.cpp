#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1005;
int n;
int x[maxn], y[maxn];
const int maxx = 2000006;
int bit[maxx];
void add(int i, int x) {
    for (; i <= 2000005; i += i & (-i)) {
        bit[i] += x;
    }
}

int sum(int i) {
    int r = 0;
    for (; i; i -= i&(-i)) {
        r += bit[i];
    }
    return r;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("intel.in","r",stdin); freopen("intel.out","w",stdout);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
        x[i] += 1e6+1;
        y[i] += 1e6+1;
    }
    x[n] = x[0];
    y[n] = y[0];
    ll htot = 0, vtot = 0;
    vector<pair<int,pair<int,int>>> horiz, vert;
    for (int i = 1; i <= n; i++) {
        if (x[i] == x[i-1]) {
            vert.push_back({x[i],{min(y[i-1],y[i]),max(y[i-1],y[i])}});
            vtot += abs(y[i]-y[i-1]);
        }
        else {
            horiz.push_back({y[i],{min(x[i-1],x[i]),max(x[i-1],x[i])}});
            htot += abs(x[i]-x[i-1]);
        }
    }
    //cout << (vtot+htot) << endl;
    sort(horiz.begin(),horiz.end(),[](auto a, auto b) {
            return a.first < b.first;
            });
    memset(bit,0,sizeof bit);
    //cout << htot << endl;
    for (auto p: horiz) {
        //cout << p.second.first << ' ' << p.second.second << '\n';
        add(p.second.first,1);
        add(p.second.second,-1);
    }
    for (int i = 1; i <= 2000001; i++) {
        if (sum(i) > 0) htot -= 2;
    }
    //cout << htot << endl;

    sort(vert.begin(),vert.end(),[](auto a, auto b) {
            return a.first < b.first;
            });
    memset(bit,0,sizeof bit);
    for (auto p: vert) {
        add(p.second.first,1);
        add(p.second.second,-1);
    }
    for (int i = 1; i <= 2000001; i++) {
        if (sum(i) > 0) vtot -= 2;
    }

    cout << (htot+vtot) << '\n';
}

