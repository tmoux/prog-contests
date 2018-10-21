#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 200005;
int n, t, A[maxn];
int freq[1000005];

struct Query
{
    int bucket, l, r, id;
    
    bool operator<(const Query& rhs) const {
        if (bucket != rhs.bucket) {
            return bucket < rhs.bucket;
        }
        else return r < rhs.r;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> t;
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
    }
    int size = (int)(sqrt(t) + 1);
    vector<Query> queries;
    for (int i = 0; i < t; i++) {
        int l, r; cin >> l >> r;
        queries.push_back({l/size,l,r,i});
    }
    sort(queries.begin(),queries.end());
    vector<ll> ans(t); 
    int L = 1, R = 1;
    ll curr = 0;
    for (Query q: queries) {
        while (L <= q.l) {
            curr -= (ll)freq[A[L]]*freq[A[L]]*A[L];
            freq[A[L]]--;
            curr += (ll)freq[A[L]]*freq[A[L]]*A[L];
            L++;
        }
        
        while (L > q.l) {
            curr -= (ll)freq[A[L-1]]*freq[A[L-1]]*A[L-1];
            freq[A[L-1]]++;
            curr += (ll)freq[A[L-1]]*freq[A[L-1]]*A[L-1];
            L--;
        }

        while (R <= q.r) {
            curr -= (ll)freq[A[R]]*freq[A[R]]*A[R];
            freq[A[R]]++;
            curr += (ll)freq[A[R]]*freq[A[R]]*A[R];
            R++;
        }

        while (R > q.r + 1) {
            curr -= (ll)freq[A[R-1]]*freq[A[R-1]]*A[R-1];
            freq[A[R-1]]--;
            curr += (ll)freq[A[R-1]]*freq[A[R-1]]*A[R-1];
            R--;
        }
        ans[q.id] = curr;
        //cout << q.l << ' ' << q.r << ' ' << L << ' ' << R << '\n';
    }

    for (int i = 0; i < t; i++) {
        cout << ans[i] << '\n';
    }

    return 0;
}
	

