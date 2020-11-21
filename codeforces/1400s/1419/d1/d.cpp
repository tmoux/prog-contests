#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<int> a;
vector<int> ret;
int n;

bool check(int mid) {
    vector<int> b(n,-1);
    bool poss = true;
    for (int i = 0; i < mid; i++) {
        if (2*i+1 >= n) {
            poss = false;
            break;
        }
        else {
            b[2*i+1] = a[i];
        }
    }
    if (!poss) return false;
    int pt = 0;
    for (int i = mid; i < n; i++) {
        while (b[pt] != -1) pt++;
        b[pt] = a[i];
        pt++;
    }
    int cnt = 0;
    for (int i = 1; i < n-1; i++) {
        if (b[i] < b[i-1] && b[i] < b[i+1]) {
            cnt++;
        }
    }
    if (cnt == mid) {
        ret = b;
        return true;
    }
    else return false;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(),a.end());
    ret = a;
    int lo = 0, hi = n;
    while (lo + 1 < hi) {
        int mid = (lo+hi)/2;
        if (check(mid)) {
            lo = mid;
        }
        else {
            hi = mid;
        }
    }
    cout << lo << '\n';
    for (auto i: ret) {
        cout << i << ' ';
    }
    cout << '\n';
}
