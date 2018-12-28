#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

const int maxn = 1e5+5;
const ll INF = 9223372036854775807;
struct Line
{
    ll m, b;
    ld intersect(const Line& r) {
        assert(m != r.m);
        return (ld)(r.b-b)/(ld)(m-r.m);
    }
    bool comp(Line& l1, Line& l2) { //true --> pop off l2
        ld x1 = l1.intersect(l2);
        ld x2 = this->intersect(l2);
        return x2 <= x1;
    }
    ll eval(ll x) {
        return m*x + b;
    }
};
ll dp[maxn];
ll a[maxn], b[maxn];
int n;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    deque<Line> deq;
    deq.push_back({b[1],dp[1]});    
    for (int i = 2; i <= n; i++) {
        ll x = a[i];
        while (deq.size() > 1 && deq[0].eval(x) >= deq[1].eval(x)) {
            deq.pop_front();
        }
        dp[i] = deq[0].eval(x);
        //add line
        Line l = {b[i],dp[i]};
        while (deq.size() > 1) {
            Line& l1 = deq[deq.size()-2];
            Line& l2 = deq[deq.size()-1];
            if (l.comp(l1,l2)) {
                deq.pop_back();
            }
            else break;
        }
        deq.push_back(l);
    }
    cout << dp[n] << '\n';

    return 0;
}

