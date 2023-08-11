#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


int p[2*1005];

void pick(int x) {
    cout << x << endl;
}

int ask() {
    int r; cin >> r;
    return r;
}

int n, m;
vector<pair<int,int>> pairs;
int paired[2*1005];

vector<int> s;

void pickBest() {
    if (!pairs.empty()) {
        pair<int,int> pp = pairs.back();
        int a = pp.first, b = pp.second;
        if (p[b] > p[a]) swap(a,b);
        pick(a);
        pairs.pop_back();
        int f = ask();
    }
    else {
        int r = *s.begin();
        pick(r);
        s.erase(s.begin());
        if (!s.empty()) {
            int f = ask();
            s.erase(remove(s.begin(),s.end(),f),s.end());
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 1; i <= 2*n; i++) cin >> p[i];
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        paired[a] = b;
        paired[b] = a;
        if (a > b) swap(a,b);
        pairs.push_back({a,b});
    }
    for (int i = 1; i <= 2*n; i++) if (!paired[i]) {
        s.push_back(i);
    }
    stable_sort(s.begin(),s.end(),[](int a, int b) {return p[a] > p[b];});
    int t; cin >> t;
    /*
    cout << "t = " << t << '\n';
    for (int p: s) {
        cout << p << ' ';
    }
    return 0;
    */
    while (!(pairs.empty() && s.empty())) {
        if (t == 1) { //my turn
            pickBest();
        }
        else {
            int r = ask();
            if (paired[r]) {
                pick(paired[r]);
                int a = r, b = paired[r];
                if (a > b) swap(a,b);
                pairs.erase(remove(pairs.begin(),pairs.end(),make_pair(a,b)),pairs.end());
                paired[a] = 0;
                paired[b] = 0;
            }
            else {
                s.erase(remove(s.begin(),s.end(),r),s.end());
                t = 1;
                pickBest();
            }
        }
    }
    return 0;
}

