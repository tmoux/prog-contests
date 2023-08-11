#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct S
{
   vector<ll> LEFT, RIGHT; 
   S () {
       LEFT.resize(3005,0);
       RIGHT.resize(3005,0);
   }
   ll ans = 0;
   void add_left(int x) {
        ans -= LEFT[x] * RIGHT[x];
        LEFT[x]++;
        ans += LEFT[x] * RIGHT[x];
   }
   void add_right(int x) {
        RIGHT[x]++;       
   }
   void remove_right(int x) {
        ans -= LEFT[x] * RIGHT[x];
        RIGHT[x]--;
        ans += LEFT[x] * RIGHT[x];
   }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        ll res = 0;
        for (int i = 0; i < n; i++) {
            S s;
            for (int j = i+2; j < n; j++) {
                s.add_right(a[j]);
            }
            for (int j = i+1; j < n; j++) {
                if (a[i] == a[j]) {
                    //cout << i << ' ' << j << ": " << s.ans << endl;
                    res += s.ans;
                }
                s.add_left(a[j]);
                if (j+1 < n) s.remove_right(a[j+1]);
            }
        }
        cout << res << '\n';
    }
}
