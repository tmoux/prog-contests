#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
const double INF = 1e30;
int N;
double a[maxn], pre[maxn];

double f(int l, int r, const vector<double>& v) {
    if (l > r) return -INF;
    if (l == r) {
        return v[l];
    }
    int m = (l+r)/2;
    double l1 = 0;
    double curr = 0;
    for (int i = m; i >= l; i--) {
        curr += v[i];
        l1 = max(l1,curr);
    }
    curr = 0;
    double l2 = 0;
    for (int i = m + 1; i <= r; i++) {
        curr += v[i];
        l2 = max(l2,curr);
    }
    double ans = l1+l2;
    return max(ans,max(f(l,m-1,v),f(m+1,r,v)));    
}

bool poss(double m) {
    vector<double> v(N+1);
    double sum = 0;
    for (int i = 1; i <= N; i++) {
        v[i] = a[i] - m;
        sum += v[i];
    }
    double maxSum = f(2,N-1,v);    
    double ans = sum - maxSum;
    //cout << m << ": " << (ans>0) << '\n';
    return ans < 0;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("sabotage.in","r",stdin); freopen("sabotage.out","w",stdout);
    cin >> N;
    a[0] = 0; pre[0] = 0;
    for (int i = 1; i <= N; i++) {
        cin >> a[i];
        pre[i] = a[i];
        pre[i] += pre[i-1];
    }
    double lo = 0, hi = 1e10;
    for (int i = 0; i < 50; i++) {
        double m = (lo+hi)/2;
        if (poss(m)) hi = m;
        else lo = m;
    }
    cout << fixed << setprecision(3) << hi << '\n';
}

