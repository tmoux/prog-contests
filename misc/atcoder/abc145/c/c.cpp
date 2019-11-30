#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define x first
#define y second

double dist(pair<int,int> a, pair<int,int> b) {
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<pair<int,int>> v(n);
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        v[i] = {x,y};
    }
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        p[i] = i;
    }
    double sum = 0;
    do {
        for (int i = 0; i < n-1; i++) {
            sum += dist(v[p[i]],v[p[i+1]]); 
        }
    } while (next_permutation(p.begin(),p.end()));
    for (int i = n; i >= 1; i--) {
        sum /= i;
    }
    cout << fixed << setprecision(10) << sum << '\n';
}

