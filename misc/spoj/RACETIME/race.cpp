#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5, sq = (int)(sqrt(maxn))+1;
int n, q, A[maxn], bucket[maxn], block;
vector<int> sorts[sq];

inline int getMultiset(const vector<int>& s, int x) {
    int ans = upper_bound(s.begin(),s.end(),x) - s.begin();
    return ans;
}

int query(int l, int r, int X) {
	int res = 0;
	if (bucket[l] == bucket[r]) {
		for (int i = l; i <= r; i++) {
			if (A[i] <= X) res++;
		}
		return res;
	}
	
	while (l != 1 && bucket[l] == bucket[l-1]) {
		if (A[l] <= X) res++;
		l++;
	}
	
	while (bucket[l] != bucket[r]) {
		res += getMultiset(sorts[bucket[l]],X);
		l += block;
	}

	for (int i = l; i <= r; i++) {
		if (A[i] <= X) res++;
	}
	
	return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    #ifdef OFFLINE
    freopen("in","r",stdin);
    #endif
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> A[i];
    //sqrt decomp
    block = (int)(sqrt(n));
	for (int i = 1; i <= n; i++) {
		bucket[i] = (i-1)/block;
		sorts[bucket[i]].push_back(A[i]);
	}
    for (int i = 0; i < sq; i++) {
        sort(sorts[i].begin(),sorts[i].end());
    }
	while (q--) {
		char c; cin >> c;
		if (c == 'M') {
			int i, X; cin >> i >> X;
            A[i] = X;
            vector<int>& vec = sorts[bucket[i]];
            vec.clear();
            for (int j = i; j >= 1 && bucket[j] == bucket[i]; j--) {
                vec.push_back(A[j]);    
            }
            for (int j = i + 1; j <= n && bucket[j] == bucket[i]; j++) {
                vec.push_back(A[j]);
            }
            sort(vec.begin(),vec.end());
		}
		else {
			int p, q, X; cin >> p >> q >> X;
			int ans = query(p,q,X);
			cout << ans << '\n';
		}
	}

    return 0;
}
