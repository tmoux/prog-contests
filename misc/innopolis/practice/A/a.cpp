#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

pair<int,pair<int,int>> gcd(int a, int b) {
    if (a == 0) return {b,{0,1}};
    if (b == 0) return {a,{1,0}};
    int x1 = 1, x2 = 0, y1 = 0, y2 = 1;
    while (a && b) {
        int r = a/b;
        int tmp = b;
        b = a - r * b;
        a = tmp;
        int tmpx = x2, tmpy = y2;
        x2 = x1 - r * x2;
        y2 = y1 - r * y2;
        x1 = tmpx, y1 = tmpy;
        //printf("%d: %d, %d\n",b,x2,y2);
    }
    return {a,{x1,y1}};
}

int mod_inverse(int x, int n) { //must check that x and n are coprime!!!
    auto ans = gcd(x,n);
    while (ans.second.first < 0) ans.second.first += n;
    return ans.second.first;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, k, s, x; cin >> n >> k >> s >> x;
    for (int i = 1; i < n; i++) {
        if ((s+i*k) % n == x) {
            cout << i << '\n';
            return 0;
        }
    }
    cout << -1 << '\n';
    /*
    if (__gcd(n,k) == 1) {
        //cout << mod_inverse(k,n) << '\n';
        int a = (mod_inverse(k,n) * (x-s+n)) % n;
        cout << a << '\n';
    }
    else {
        if (x < s) x += n;
        if ((x-s) % k == 0) {
            cout << (x-s)/k << '\n';
        }
        else {
            cout << -1 << '\n';
        }
    }
    */

    return 0;
}

