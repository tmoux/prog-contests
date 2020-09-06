#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int Div[] = {1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};
class SortInversions
{
public:
    int nd(ll x) {
        int ans = 0;
        while (x > 0) {
            ans++;
            x /= 10;
        }
        return ans;
    }
    ll count(int N_) {
        ll N = N_;
        ll b = 0;
        ll st = 0;
        ll ans = 0;

        int curd = 1;
        while (b+100-1 <= N) {
            if (b == 0) {
                ans += 360;
            }
            else {
                ans += st*100-10*45;
            }

            b += 100;
            int newd = nd(b);
            if (newd > curd) {
                st = b - newd;
                curd = newd;
            }
            else {
                for (int i = 8; i >= 2; i--) {
                    if ((b/Div[i])*Div[i] == b) {
                        st -= 9+i;
                        break;
                    }
                }
            }
            /*
            cout << "b = " << b << endl;
            cout << b << ": st = " << st << endl;
            */
        }
        while (b <= N) {
            ans += st;
            b++;
            if (b == 10) st = 8;
            else if (b % 10 == 0) st--;
        }
        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    auto calc = [](int n) { 
        vector<string> a(n);
        for (int i = 0; i < n; i++) {
            a[i] = to_string(i+1);
        }
        sort(a.begin(),a.end());
        vector<int> b;
        for (auto s: a) {
            int x = 0;
            for (int i = 0; i < s.size(); i++) {
                x *= 10;
                x += (s[i]-'0');
            }
            b.push_back(x);
        }
        int inv = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (b[i] < b[j]) inv++;
            }
        }
        return inv;
    };
    int n; cin >> n;
    SortInversions t;
    cout << t.count(n) << endl;
    //cout << n << ": " << t.count(n) << ' ' << calc(n) << endl;
    /*
    for (int i = 1; i <= n; i++) {
        cout << i << ": " << (calc(i)-calc(i-1)) << '\n';
    }
    */
    /*
    for (auto s: b) {
        cout << s << ' ';
    }
    cout << '\n';
    cout << "inv = " << inv << endl;
    */
}
