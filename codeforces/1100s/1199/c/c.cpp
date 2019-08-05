#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 4e5+5;
int n;
ll I;
int a[maxn];
int pre[maxn];


int ceilLg2(int x) {
    int res = 0;
    while (1<<res < x) res++;
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> I;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    I *= 8; //now I is in bits
    ll lo = 0, hi = n+1;
    while (lo + 1 < hi) {
        ll mid = (lo+hi)/2;
        ll k = ceilLg2(mid);
        //cout << mid << ' ' << k << '\n';
        if (k*n <= I) {
            lo = mid;
        }
        else hi = mid;
    }
    ll numDistinct = lo;
    sort(a+1,a+1+n);
    vector<int> v;
    int curr = -1, cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] != curr) {
            if (curr != -1) {
                v.push_back(cnt);
            }
            curr = a[i];
            cnt = 1;
        }
        else {
            cnt++;
        }
    }
    v.push_back(cnt);
    /*
    for (int i: v) {
        cout << i << ' ';
    }
    cout << '\n';
    */
    //cout << "num distinct " << numDistinct << '\n';
    for (int i = 0; i < v.size(); i++) {
        pre[i+1] = v[i];
        pre[i+1] += pre[i];
        //cout << i << ": " << pre[i] << '\n';
    }
    if (numDistinct > v.size()) {
        cout << 0 << '\n';
        return 0;
    }
    int maxans = 0;
    for (int i = numDistinct; i <= v.size(); i++) {
        maxans = max(maxans,pre[i]-pre[i-numDistinct]);
        //cout << i << ": " << (pre[i]-pre[i-numDistinct]) << '\n';
    }
    cout << (n-maxans) << '\n';
}

