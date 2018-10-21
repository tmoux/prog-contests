#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5, sq = (int)(sqrt(maxn))+5;
int N, Q;
struct Point { int x, y; };
Point A[maxn];
int block, bucket[maxn], sum[sq], mdelta[sq], start[sq]; 
inline int dist(Point& a, Point& b) {
	return abs(a.x-b.x) + abs(a.y-b.y);
}
inline int delta(Point& a, Point& b, Point c) {
	return dist(a,b) + dist(b,c) - dist(a,c);
}

void updateBlock(int b) {
	int s = start[b];
	sum[b] = 0;
	mdelta[b] = 0;
	for (int i = s; i < N - 1 && bucket[i] == b; i++) {
		sum[b] += dist(A[i],A[i+1]);
		//cout << b << ": " << i << ' ' << i+1 << ' ' << dist(A[i],A[i+1]) << '\n';
	}
	for (int i = s; i < N - 1 && bucket[i] == b; i++) {
		if (i == 0 || i == N - 1) continue;
		mdelta[b] = max(mdelta[b],delta(A[i-1],A[i],A[i+1]));
	}
}

int query(int i, int j) {
	int tot = 0;
	for (int s = i; s < j;) {
		if (s == 0 || bucket[s] != bucket[s-1]) {
			tot += sum[bucket[s]];
			s += block;
		}
		else {
			tot += dist(A[s],A[s+1]);
			s++;
		}
	}
	int d = 0;
	for (int s = i+1; s < j;) {
		if (bucket[s] != bucket[s-1]) {
			d = max(d,mdelta[bucket[s]]);
			s += block;
		}
		else {
			d = max(d,delta(A[s-1],A[s],A[s+1]));
			s++;
		}
	}
	//cout << tot << ' ' << d << '\n';
	return tot-d;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("marathon.in","r",stdin);
    freopen("marathon.out","w",stdout);
    cin >> N >> Q;
    for (int i = 0; i < N; i++) {
    	cin >> A[i].x >> A[i].y;
    }
    block = (int)(sqrt(N));
    for (int i = 0; i < N; i++) {
    	bucket[i] = i/block;
    	if (i == 0 || bucket[i-1] != bucket[i]) {
    		start[bucket[i]] = i;
    	}
    } 
    for (int i = 0; i <= bucket[N-1]; i++) {
    	updateBlock(i);
    	//cout << sum[i] << ' ' << mdelta[i] << '\n';
    }

    
    while (Q--) {
    	char c; cin >> c;
    	if (c == 'U') {
    		int i, x, y; cin >> i >> x >> y;
    		i--;
    		A[i] = {x,y};
    		updateBlock(bucket[i]);
    		if (i > 0 && bucket[i-1] != bucket[i]) updateBlock(bucket[i-1]);
    		if (i < N - 1 && bucket[i+1] != bucket[i]) updateBlock(bucket[i+1]);
    	}
    	else {
    		int i, j; cin >> i >> j;
    		i--;
    		j--;
    		if (i == j) {
    			cout << 0 << '\n';
    			continue;
    		}
    		int ans = query(i,j);
    		cout << ans << '\n';
    	}
    }
    /*
    for (int i = 1; i <= N - 1; i++) {
    	cout << i << ' ' << delta(A[i-1],A[i],A[i+1]) << '\n';
    }
    */

    return 0;
}




