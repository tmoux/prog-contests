const int maxn = 1e5+5;

struct Seg
{
	int *s, *e, *sum;
	Seg(int l, int r, int *a) {
		int n = r-l+1;
		s = new int[4*n];
		e = new int[4*n];
		sum = new int[4*n];
		build(1,l,r,a);
	}
	void build(int i, int l, int r, int *a) {
		s[i] = l;
		e[i] = r;
		if (l == r) {
			sum[i] = a[l];
			return;
		}
		int m = (l+r)/2;
		build(i*2,l,m,a);
		build(i*2+1,m+1,r,a);
		sum[i] = sum[i*2] + sum[i*2+1];
	}
	void update(int i, int idx, int x) {
		//add x to a[idx];
		if (e[i] < idx || s[i] > idx) return;
		if (s[i] == idx && e[i] == idx) {
			sum[idx] += x;
			return;
		}
		update(i*2,idx,x);
		update(i*2+1,idx,x);
	}
	int getsum(int i, int l, int r) {
		if (e[i] < l || s[i] > r) return 0;
		if (l <= s[i] && e[i] <= r) return sum[i];
		return getsum(i*2,l,r)+getsum(i*2+1,l,r);
	}
};