#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<ll,ll>;
using state = pair<pi,int>;

const int maxn = 3e5+5;
vector<state> v;
int n;

struct cmp1 {
    bool operator()(state a, state b) {
        return a.first.second != b.first.second ? a.first.second > b.first.second : a.second > b.second;
    }
};
struct cmp2 {
    bool operator()(state a, state b) {
        return a.first.first+a.first.second != b.first.first+b.first.second ? a.first.first+a.first.second > b.first.first+b.first.second : a.second > b.second;
    }
};
struct cmp3 {
    bool operator()(state a, state b) {
        return a.first.first != b.first.first ? a.first.first > b.first.first : a.second > b.second;
    }
};


vector<int> ans;

vector<state> s2;

vector<int> maybe;
bool used[maxn];

random_device device;
mt19937 gen(device());
bool poss(ll maxd) {
    //cout << maxd << endl;
    memset(used,0,sizeof used);
    priority_queue<state,vector<state>,cmp1> s1;
    priority_queue<state,vector<state>,cmp3> s1Q;

    priority_queue<state,vector<state>,cmp3> s3;
    priority_queue<state,vector<state>,cmp1> s3Q;
    maybe.clear();
    ll X = 1, Y = 1;    

    ll mX = 1, mY = 1;
    shuffle(v.begin(),v.end(),gen);
    for (int _ = 0; _ < 5; _++) {
        for (int i = 0; i < v.size(); i++) {
            if (used[v[i].second]) continue;
            if (v[i].first.first <= (ll)X+maxd &&
                v[i].first.second <= (ll)Y+maxd &&
                (ll)v[i].first.first+v[i].first.second <= (ll)X+Y+maxd) {

                maybe.push_back(v[i].second);
                used[v[i].second] = true;
                X = max(X,v[i].first.first);
                Y = max(Y,v[i].first.second);
            }
        }
    }
    int pt = 0;
    for (int _ = 0; _ < n+10; _++) {
        while (pt < s2.size()) {
            if (used[s2[pt].second]) {
                pt++;
                continue;
            }
            pi p = s2[pt].first;
            if ((ll)p.first+p.second <= (ll)X+Y+maxd) {
                auto pp = s2[pt];
                pt++;
                s1Q.push(pp);
                s3Q.push(pp);
            }
            else break;
        }
        while (!s1Q.empty()) {
            auto pp = s1Q.top();
            pi p = pp.first;
            if ((ll)p.first <= (ll)X+maxd) {
                s1Q.pop();
                s1.push(pp);
            }
            else break;
        }
        while (!s3Q.empty()) {
            auto pp = s3Q.top();
            pi p = pp.first;
            if ((ll)p.second <= (ll)Y+maxd) {
                s3Q.pop();
                s3.push(pp);
            }
            else break;
        }
        bool stop = true;
        while (!s1.empty()) {
            auto pp = s1.top();
            pi p = pp.first;
            if ((ll)p.first <= (ll)X+maxd && (ll)p.second <= (ll)Y+maxd) {
                int id = pp.second;
                s1.pop();
                if (!used[id]) {
                    used[id] = true;
                    maybe.push_back(id);
                    X = max(X,p.first);
                    Y = max(Y,p.second);
                    stop = false;
                }
            }
            else break;
        }
        while (!s3.empty()) {
            auto pp = s3.top();
            pi p = pp.first;
            if ((ll)p.first <= (ll)X+maxd && (ll)p.second <= (ll)Y+maxd) {
                int id = pp.second;
                s3.pop();
                if (!used[id]) {
                    used[id] = true;
                    maybe.push_back(id);
                    X = max(X,p.first);
                    Y = max(Y,p.second);
                    stop = false;
                }
            }
            else break;
        }
        if (stop) break;
    }
    //cout << maxd << ": " << (maybe.size()==n) << endl;
    if (maybe.size() == n) {
        ans = maybe;
        return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    v.resize(n);
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        v[i] = {{x,y},i};
        s2.push_back(v[i]);
    }
    sort(s2.begin(),s2.end(),[](auto a, auto b) {
            if (a.first.first+a.first.second != b.first.first+b.first.second) return a.first.first+a.first.second < b.first.first + b.first.second;
            return a.second < b.second;
            });
    ll lo = 0, hi = 2e9+9;
    if (poss(0)) {
        for (int i = 1; i <= n; i++) {
            cout << i << ' ';
        }
        cout << '\n';
        return 0;
    }
    while (lo + 1 < hi) {
        int mid = (lo+hi)/2;
        if (poss(mid)) hi = mid;
        else lo = mid;
    }
    //assert(!ans.empty());
    //cout << "min = " << hi << endl;
    for (auto i: ans) {
        cout << i+1 << ' ';
    }
    cout << '\n';
    //cout << hi << '\n';
}
