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

/*
set<state,decltype(cmp1)> s1(cmp1);
set<state,decltype(cmp3)> s1Q(cmp3);

set<state,decltype(cmp2)> s2(cmp2);

set<state,decltype(cmp3)> s3(cmp3);
set<state,decltype(cmp1)> s3Q(cmp1);
*/

vector<int> ans;

vector<int> maybe;
vector<state> s2;
bool used[maxn];
bool poss(ll maxd) {
    memset(used,0,sizeof used);
    priority_queue<state,vector<state>,cmp1> s1;
    priority_queue<state,vector<state>,cmp3> s1Q;

    priority_queue<state,vector<state>,cmp3> s3;
    priority_queue<state,vector<state>,cmp1> s3Q;
    maybe.clear();
    ll X = 1, Y = 1;    
    int pt = 0;
    while (true) {
        while (pt < s2.size()) {
            pi p = s2[pt].first;
            if (p.first+p.second <= X+Y+maxd) {
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
            if (p.first <= X+maxd) {
                s1Q.pop();
                s1.push(pp);
            }
            else break;
        }
        while (!s3Q.empty()) {
            auto pp = s3Q.top();
            pi p = pp.first;
            if (p.second <= Y+maxd) {
                s3Q.pop();
                s3.push(pp);
            }
            else break;
        }
        bool stop = true;
        while (!s1.empty()) {
            auto pp = s1.top();
            pi p = pp.first;
            int id = pp.second;
            if (p.first <= X+maxd && p.second <= Y+maxd) {
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
            int id = pp.second;
            if (p.first <= X+maxd && p.second <= Y+maxd) {
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
}

