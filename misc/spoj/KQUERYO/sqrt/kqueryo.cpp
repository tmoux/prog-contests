#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 3e4+5, sq = (int)(sqrt(maxn))+2;
int n, q, A[maxn], bucket[maxn], block[sq][maxn], block_size;

int nGreater(int l, int r, int x) {
    int res = 0;
    if (bucket[l] == bucket[r]) {
        for (int i = l; i <= r; i++) {
            if (A[i] >= x) res++;
        }
        return res;
    }
    while (l != 1 && bucket[l] == bucket[l-1]) {
        if (A[l] >= x) res++;
        l++;
    }
    while (bucket[l] != bucket[r]) {
        res += block[bucket[l]][x];
        l += block_size;
    }
    for (int i = l; i <= r; i++) {
        if (A[i] >= x) res++;
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    memset(block,0,sizeof(block));
    cin >> n;
    vector<pair<int,int>> v;
    for (int i = 1; i <= n; i++) {
        int ai; cin >> ai;
        v.push_back({ai,i});
    } //coordinate compression
    sort(v.begin(),v.end());
    for (int i = 0; i < v.size(); i++) {
        A[v[i].second] = i;
    }
    //sqrt decomp
    block_size = (int)(sqrt(n));
    for (int i = 1; i <= n; i++) {
        bucket[i] = (i-1)/block_size;
    }
    vector<int> curr;
    for (int i = 1; i <= n; i++) {
        curr.push_back(A[i]);
        if (i == n || bucket[i] != bucket[i+1]) {
            sort(curr.begin(),curr.end());
            for (int j = n; j >= 0; j--) {
                block[bucket[i]][j] = block[bucket[i]][j+1];
                if (curr.empty()) continue;
                if (j == curr.back()) {
                    block[bucket[i]][j]++;
                    curr.pop_back();
                }
            }
            curr.clear();
        }
    }

    cin >> q;
    int last_ans = 0;
    while (q--) {
        int l, r, x; cin >> l >> r >> x;
        l ^= last_ans;
        r ^= last_ans;
        x ^= last_ans;
        if (l < 1) l = 1;
        if (r > n) r = n;
        if (l > r) {
            last_ans = 0;
            cout << last_ans << '\n';
            continue;
        }
        pair<int,int> p = {x,2e9};
        x = upper_bound(v.begin(),v.end(),p)-v.begin();
        last_ans = nGreater(l,r,x);
        cout << last_ans << '\n';
    }
    return 0;
}
	

