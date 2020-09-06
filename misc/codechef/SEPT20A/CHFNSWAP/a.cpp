#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll brute(ll N) {
    vector<int> a(N);
    for (int i = 0; i < N; i++) {
        a[i] = i+1;
    }
    ll n2 = N*(N+1)/2;
    if (n2 % 2 != 0) {
        return 0;
    }
    else {
        ll ans = 0;
        ll target = n2/2;
        for (int i = 0; i < N; i++) {
            for (int j = i+1; j < N; j++) {
                swap(a[i],a[j]);
                ll sum = 0;
                for (int k = 0; k < N; k++) {
                    sum += a[k];
                    if (sum == target) {
                        ans++;
                        break;
                    }
                }
                swap(a[i],a[j]);
            }
        }
        return ans;
    }
}

ll ch2(ll x) {
    return x*(x-1)/2;
}

ll solve(ll N) {
    ll n2 = N*(N+1)/2;
    if (n2 % 2 != 0) {
        return 0;
    }
    else if (N == 3) {
        return 2;
    }
    else {
        ll target = n2/2;
        ll lo = 0, hi = N;
        while (lo + 1 < hi) {
            ll mid = (lo+hi)/2;
            ll need = target-((mid*(mid+1))/2);
            if (need == 0) {
                hi = mid;
            }
            else if (need < 0) {
                hi = mid;
            }
            else {
                ll R = min(mid,N-need);
                if (R < 1) {
                    lo = mid;
                }
                else {
                    hi = mid;
                }
            }
        }
        ll ans = 0;
        //cout << N << ": " << "lo = " << lo << endl;
        for (ll i = lo; i < N; i++) {
            ll sum = i*(i+1)/2;
            ll need = target-sum;
            if (need == 0) {
                ans += ch2(i);
                ans += ch2(N-i);
            }
            else if (need < 0) break;
            else {
                ll L = max(1LL,i+1-need);
                ll R = min(i,N-need);
                //cout << i << ": " << L << ' ' << R << endl;
                ans += max(R-L+1,0LL);
            }
            //cout << "ans = " << ans << endl;
        }
        return ans;
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    /*
    for (ll i = 1; ; i++) {
        ll a = solve(i);
        ll b = brute(i);
        if (a == b) {
            cout << "ok " << i << endl;
        }
        else {
            cout << "wrong " << i << ": " << a << ' ' << b << endl;
            assert(false);
        }
    }
    return 0;
    */
    int t; cin >> t;
    while (t--) {
        ll N; cin >> N;
        cout << solve(N) << '\n';
        //cout << solve(N) << " :: " << brute(N) << '\n';
    }
}
