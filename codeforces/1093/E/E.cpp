#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5+5, sq = (int)(sqrt(maxn)) + 3;
int n, m, a[maxn], b[maxn];
int block, pfx[sq][maxn], bucket[maxn], first[sq];

void add(int i, int x, int bit[]) {
    for (; i <= n; i += i & (-i))
        bit[i] += x;
}

int sum(int i, int bit[]) {
    int r = 0;
    for (; i; i -= i & (-i)) {
        r += bit[i];
    }
    return r;
}

void addToSqrt(int i, int x) {
	//adds x to idx i
	//updates bucket[i] to bucket[n]
	for (int j = bucket[i]; j <= bucket[n]; j++) {
		add(x,1,pfx[j]);
	}
}
void removeFromSqrt(int i, int x) {
	for (int j = bucket[i]; j <= bucket[n]; j++) {
		add(x,-1,pfx[j]);
	}
}

int countRange(int la, int ra, int i) {
    if (i == 0) return 0;
	int cnt = sum(ra,pfx[bucket[i]-1]) - sum(la-1,pfx[bucket[i]-1]);
	for (int j = first[bucket[i]]; j <= i; j++) {
		if (la <= b[j] && b[j] <= ra) {
			cnt++;
		}
	}
	return cnt;
}

int main()
{
    scanf("%d %d",&n,&m);
    for (int i = 1; i <= n; i++) {
        int ai; scanf("%d",&ai);
        a[ai] = i;
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d",b+i);
        b[i] = a[b[i]];    
    }
    //sqrt-decomposition on array:
    //every sqrt(N) indices, keep a "snapshot" of prefixes
    //every update, add and remove sqrt(N) blocks
    //every query, count in sqrt(N) time
    block = 7*(int)(sqrt(n)) + 1;
    //block size matters a lot! Aim for few # of blocks over small block size
    //optimal size seems to be around 7*sqrt(n)
    for (int i = 1; i <= n; i++) {
    	bucket[i] = (i-1)/block + 1;
    	if (bucket[i] != bucket[i-1]) first[bucket[i]] = i;
    }
    //nobody lives in the 0 bucket
    for (int i = 1; i <= n; i++) {
    	addToSqrt(i,b[i]);
    }
    //answer queries
    while (m--) {
    	int t; scanf("%d",&t);
    	if (t == 1) {
    		int la, ra, lb, rb; scanf("%d %d %d %d",&la,&ra,&lb,&rb);
    		int a1 = countRange(la,ra,rb);
    		int a2 = countRange(la,ra,lb-1);
            printf("%d\n",a1-a2);
            /*
            for (int i = bucket[1]; i <= bucket[n]; i++) {
                for (int j = 1; j <= n; j++) {
                    cout << sum(j,pfx[i]) - sum(j-1,pfx[i]) << ' ';
                }
                cout << '\n';
            }
            */
            /*
            for (int i = 1; i <= n; i++) {
                cout << b[i] << ' ';
            }
            cout << '\n';
            */
    	}
    	else {
    		int x, y; scanf("%d %d",&x,&y);
    		removeFromSqrt(x,b[x]);
            removeFromSqrt(y,b[y]); 
    		addToSqrt(y,b[x]);
    		addToSqrt(x,b[y]);
    		swap(b[x],b[y]);
    	}
    }

    return 0;
}
