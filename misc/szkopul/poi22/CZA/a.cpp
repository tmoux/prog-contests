#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6;
int n, k, p;

set<int> no[maxn];
const int M = 1e9+7;
void madd(int& a, int b) {
    a = (a+b) % M;
}

bool check(const vector<int>& v) {
    for (int i = 0; i < v.size(); i++) {
        if (no[v[i]].count(v[(i+1)%v.size()])) return false;
        if (abs(v[i]-v[(i+1)%v.size()]) > p) return false;
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> k >> p;
    for (int i = 0; i < k; i++) {
        int a, b; cin >> a >> b;
        no[a].insert(b);
    }
    //brute force
    if (n <= 9) {
        int ans = 0;
        vector<int> perm = {n};
        for (int i = 1; i < n; i++) {
            perm.push_back(i);
        }
        do {
            if (check(perm)) {
                ans++;    
                for (int i: perm) {
                    cout << i << ' ';
                }
                cout << '\n';
            }
        } while (next_permutation(perm.begin()+1,perm.end()));
        cout << ans << '\n';
        return 0;
    }
    //do it by cases
    if (p == 0) {
        cout << (n == 1 ? 1 : 0) << '\n';
    }
    else if (p == 1) {
        if (n == 1) {
            cout << 1 << '\n';
        }
        else if (n == 2) {
            cout << (k == 1 ? 0 : 1) << '\n';
        }
        else {
            cout << 0 << '\n';
        }
        return 0;
    }
    else if (p == 2) {
        vector<int> a1;
        for (int i = n; i >= 1; i -= 2) {
            a1.push_back(i);
        }
        for (int i = (n%2==0?1:2); i < n; i += 2) {
            a1.push_back(i);    
        }
        vector<int> a2 = {n};
        for (int i = n-1; i >= 1; i -= 2) {
            a2.push_back(i);
        }
        for (int i = (n%2==0?2:1); i < n; i += 2) {
            a2.push_back(i);
        }
        int ans = 0;
        if (check(a1)) ans++;
        if (check(a2)) ans++;
        /*
        for (int i: a1) {
            cout << i << ' ';
        }
        cout << '\n';
        for (int i: a2) {
            cout << i << ' ';
        }
        cout << '\n';
        */
        cout << ans << '\n';
    }
    else {
        assert(p == 3);
        //use dp[n][1<<6]

    }
}

