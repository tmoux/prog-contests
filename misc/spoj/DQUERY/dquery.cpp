#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <map>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 3e4+5, maxq = 2e5+5;
const int maxx = 1000006;
int n, q, ans[maxq];
int A[maxn];
int freq[maxx];

struct Query
{
    int bucket, l, r, id;
    bool operator<(const Query& rhs) {
        if (bucket != rhs.bucket) {
            return bucket < rhs.bucket;
        }
        else return r < rhs.r;
    }
};

void remove(int i, int& curr) {
    freq[A[i]]--;
    if (freq[A[i]] == 0) curr--;
}

void add(int i, int& curr) {
    freq[A[i]]++;
    if (freq[A[i]] == 1) curr++;
}

int main()
{
    #ifdef OFFLINE
    freopen("in","r",stdin);
    #endif
    scanf("%d\n",&n);
    for (int i = 1; i <= n; i++) {
        scanf("%d",A+i);
    }
    
    vector<Query> queries;
    scanf("%d",&q);
    int size = (int)sqrt(q+1);
    for (int i = 0; i < q; i++) {
        int l, r; scanf("%d %d",&l,&r);
        queries.push_back({l/size,l,r,i});
    }
    sort(queries.begin(),queries.end());
    int L = 1, R = 1;
    int curr = 0;
    for (Query& q: queries) {
        while (L <= q.l) {
            remove(L,curr);     
            L++;
        }
        while (L > q.l) {
            add(L-1,curr);
            L--;
        }

        while (R <= q.r) {
            add(R,curr);
            R++;
        }
        while (R > q.r + 1) {
            remove(R-1,curr);
            R--;
        }

        ans[q.id] = curr;
        //cout << q.id << ": " << curr << '\n';
    }

    for (int i = 0; i < q; i++) {
        printf("%d\n",ans[i]);
    }

    return 0;
}
	

