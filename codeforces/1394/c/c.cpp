#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5, INF = 2e9;
int n;
pair<int,int> a[maxn];
pair<int,int> ans = {-1,-1};
vector<int> v[500005];

struct Bag {
    multiset<int> lb = {-INF};
    multiset<int> ub = {INF};
    int aux_lb = 0;
    int aux_ub = 0;

    int get_lb() {
        return *lb.rbegin() + aux_lb;
    }
    void incr_lb() {
        aux_lb++;
    }
    int get_ub() {
        return *ub.begin() + aux_ub;
    }
    void incr_ub() {
        aux_ub++;
    }
    void add(int x, int y) {
        lb.insert(x-aux_lb);
        ub.insert(y-aux_ub);
    }
    void remove(int x, int y) {
        auto it = lb.find(x);
        lb.erase(it);
        it = ub.find(y);
        ub.erase(y);
    }
};

int mn = INF, mx = -INF;

pair<int,int> orig[maxn];

bool check(int x) {
    Bag bot, top;    
    if (mn + 2*x < mx) return false;
    int st = max(mn,mx-x);
    //cout << "st = " << st << endl;
    for (int i = 0; i < n; i++) {
        if (a[i].first < st) {
            int dist = st-a[i].first;
            assert(dist <= x);
            orig[i] = {a[i].second-(x-dist),a[i].second+x};
            bot.add(orig[i].first,orig[i].second);
        }
        else {
            int dist = a[i].first-st;
            assert(dist <= x);
            orig[i] = {a[i].second-x,a[i].second+(x-dist)};
            top.add(orig[i].first,orig[i].second);
        }
        //cout << i << ": " << orig[i].first << ' ' << orig[i].second << '\n';
    }
    for (int i = st; i <= min(mn+x,mx); i++) {
        for (int id: v[i]) {
            top.remove(orig[id].first,orig[id].second);
            bot.add(a[id].second-x,a[id].second+x);
        }
        
        int lb = max(bot.get_lb(),top.get_lb());
        int ub = min(bot.get_ub(),top.get_ub());
        //cout << "i = " << i << ", bot lb = " << bot.get_lb() << endl;
        if (lb <= ub && !(i == 0 && ub == 0)) {
            //cout << i << ": " << "found " << lb << ' ' << ub << endl;
            ans = {i,ub};
            return true;
        }
        bot.incr_lb();
        top.incr_ub();
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    map<pair<int,int>,int> mp;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        pair<int,int> p = {0,0};
        for (char c: s) {
            if (c == 'B') p.first++;
            else p.second++;
        }
        mp[p]++;
        mn = min(mn,p.first);
        mx = max(mx,p.first);
        //cout << a[i].first << ' ' << a[i].second << '\n';
    }
    n = mp.size();
    int pt = 0;
    for (auto pa: mp) {
        pair<int,int> p = pa.first;
        a[pt] = p;
        v[p.first].push_back(pt);
        pt++;
    }
    int lo = -1, hi = 1000005;
    //check(24);
    //return 0;
    while (lo + 1 < hi) {
        int mid = (lo+hi)/2;
        bool c = check(mid);
        //cout << "checking " << mid << ": " << c << endl;
        if (c) {
            hi = mid;
        }
        else {
            lo = mid;
        }
    }
    cout << hi << '\n';
    for (int i = 0; i < ans.first; i++) cout << 'B';
    for (int i = 0; i < ans.second; i++) cout << 'N';
    cout << '\n';
    //cout << ans.first << ' ' << ans.second << endl;
}
