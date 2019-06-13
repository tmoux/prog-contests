#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n;
deque<int> a, b;
set<int> aa, bb;

bool check(int num) {
    set<int> use = aa;
    deque<int> cp = b;
    for (int i = 0; i < n; i++) {
        if (a[i] == 0 && num > 0) {
            int f = cp.front();
            cp.pop_front();
            if (f > 0) use.insert(f);
            num--;
        }
    }
    /*
    cout << "checking " << num << '\n';
    for (int i: use) {
        cout << i << ' ';
    }
    cout << '\n';
    */
    for (int i = 1; i <= n; i++) {
        if (!use.count(i)) return false;
        cp.push_back(i);
        int f = cp.front();
        cp.pop_front();
        if (f > 0) use.insert(f);
    }
    return true;
}

int pos[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        a.push_back(ai);
        if (ai != 0) {
            aa.insert(ai);
            pos[ai] = 0;
        }
    }
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        b.push_back(ai);
        if (ai != 0) {
            bb.insert(ai);
            pos[ai] = i+1;
        }
    }
    if (a.empty()) {
        bool poss = true;
        for (int i = 0; i < n; i++) {
            if (b[i] != i + 1) {
                poss = false;
                break;
            }
        }
        if (poss) {
            cout << 0 << '\n';
            return 0;
        }
    }
    set<int> test = aa;
    deque<int> d = b;
    int ans = 0;
    while (!test.empty()) {
        int mn = *test.begin();
        test.erase(test.begin());
        d.push_back(mn);
        if (d.front() > 0) test.insert(d.front());
        d.pop_front();
        ans++;
    }
    bool poss = true;
    assert(d.size() == n);
    for (int i = 0; i < n; i++) {
        if (d[i] != i + 1) poss = false;
    }
    if (poss) {
        cout << ans << '\n';
        return 0;
    }
    ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = max(ans,pos[i]-i+1+n);
    }
    cout << ans << '\n';
}

