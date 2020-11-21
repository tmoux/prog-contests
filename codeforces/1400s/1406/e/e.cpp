#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
bool prime[maxn];

bool on[maxn];
int n;

int del(int i) {
    int res = 0;
    for (int j = i; j <= n; j += i) {
        if (on[j]) {
            on[j] = false;
            res++;
        }
    }
    return res;
}

int aska(int a) {
    cout << "A " << a << endl;
    int x; cin >> x;
    return x;
}

int askb(int a) {
    assert(a > 1);
    cout << "B " << a << endl;
    int x; cin >> x;
    return x;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 2; i <= n; i++) prime[i] = true;
    for (int i = 2; i <= n; i++) {
        if (prime[i]) {
            for (int j = 2*i; j <= n; j += i) {
                prime[i] = false;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        on[i] = true;
    }
    int ans = 1;
    int tot = n;
    int BLK = 5;
    vector<int> q;
    for (int i = 2; i <= n; i++) {
        if (prime[i]) {
            tot -= del(i);
            q.push_back(i);
        }
        if (q.size() >= BLK) {
            for (auto j: q) {
                int ac_count = 
            }
            q.clear();
        }
    }
