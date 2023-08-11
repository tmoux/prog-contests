#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 21, sz = 2*(1 << maxn);
pair<ll,ll> agg[maxn];
int n, A[1 << maxn], q;
vector<int> mergesort[sz];

int left(int x) { return 2*x; }
int right(int x) { return 2*x+1; }

ll countInversions(vector<int>& vec, vector<int>& a, vector<int>& b) {
    ll res = 0LL;
    int i = 0, j = 0;
    while (i < a.size() && j < b.size()) {
        if (a[i] <= b[j]) {
            vec.push_back(a[i]);
            i++;
        }
        else {
            vec.push_back(b[j]);
            j++;
            res += a.size() - i;
        }
    }
    for (; i < a.size(); i++) vec.push_back(a[i]);
    for (; j < b.size(); j++) vec.push_back(b[j]);
    return res;
}

void build(int i, int start, int end, int dep) {
    if (start == end) {
        mergesort[i] = {A[start]};
        return;
    }
    int mid = (start + end) >> 1;
    build(left(i),start,mid,dep+1);
    build(right(i),mid+1,end,dep+1);
    vector<int> &vec = mergesort[i], rev, &lvec = mergesort[left(i)], &rvec = mergesort[right(i)];
    agg[dep].first += countInversions(vec,lvec,rvec);
    agg[dep].second += countInversions(rev,rvec,lvec);
}

void solve(int qi) {
    for (int i = qi; i <= n; i++) {
        swap(agg[i].first,agg[i].second);
    }
    ll ans = 0;
    for (int i = 0; i <= n; i++) {
        ans += agg[i].first;
    }
    cout << ans << '\n';
}
    
int main()
{
    scanf("%d",&n);
    for (int i = 0; i < (1 << n); i++) {
        scanf("%d",A+i);
    }
    build(1,0,(1<<n)-1,0);
    scanf("%d",&q);
    while (q--) {
        int qi; scanf("%d",&qi);
        solve(n-qi);
    }
    
    return 0;
}
