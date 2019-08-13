#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 998244353, maxn = 2e5+5;
struct Point
{
    int x, y;
} pts[maxn];
int N;

struct Node {
	int s, e, m;
	//covers s,e;
	int sum;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		sum = 0;
		if (s != e) {
			m = (s+e)/2;
			l = new Node(s,m);
			r = new Node(m+1,e);
		}
		else {
			l = NULL;
			r = NULL;
		}
	}

	void add(int i, int x) {
		if (s == e) {
			sum += x;
			return;
		}
		if (i <= m) {
			l->add(i,x);
		}
		else if (i > m) {
			r->add(i,x);
		}
		else assert(false);
		sum = l->sum + r->sum;
	}

	int getsum(int st, int en) {
        assert(st <= en);
		if (st <= s && e <= en) {
			return sum;
		}
		int ret = 0;
		if (st <= m) {
			ret += l->getsum(st,en);
		}
		if (en > m) {
			ret += r->getsum(st,en);
		}
		return ret;
	}
};

int modexp(int a, int b) {
    int res = 1;
    while (b > 0) {
        if (b&1) res = (1LL*res*a) % M;
        a = (1LL*a*a) % M;
        b >>= 1;
    }
    return res;
}

void madd(int& a, int b) {
    a = (a+b) % M;
}
void msub(int& a, int b) {
    a = (a-b+M) % M;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    set<int> xs, ys;
    for (int i = 0; i < N; i++) {
        int x, y; cin >> x >> y;
        pts[i] = {x,y};
        xs.insert(x);
        ys.insert(y);
    }
    int pt = 1;
    sort(pts,pts+N,[](auto a, auto b) {
            return a.x < b.x;
            });
    for (int i = 0; i < N; i++) {
        pts[i].x = pt++;
    }
    pt = 1;
    sort(pts,pts+N,[](auto a, auto b) {
            return a.y < b.y;
            });
    for (int i = 0; i < N; i++) {
        pts[i].y = pt++;
    }
    //now they are compressed
    sort(pts,pts+N,[](auto a, auto b) {
            return a.x < b.x;
            });
    Node *root = new Node(0,N+1);
    int ans = 0;
    for (int i = 0; i < N; i++) {
        //cout << i << endl;
        int x = pts[i].x;
        int y = pts[i].y;
        madd(ans,modexp(2,N));
        //take out up, down, left, right
        msub(ans,modexp(2,N-y));
        msub(ans,modexp(2,y-1));
        msub(ans,modexp(2,N-x));
        msub(ans,modexp(2,x-1));
        //add back corners
        int leftup = root->getsum(y,N);
        madd(ans,modexp(2,leftup));
        madd(ans,modexp(2,(N-y)-leftup));

        int leftdown = root->getsum(1,y);
        /*
        cout << x << ' ' << y << '\n';
        cout << "left up : " << leftup << '\n';
        cout << "left down : " << leftdown << '\n';
        */
        madd(ans,modexp(2,leftdown));
        madd(ans,modexp(2,(y-1)-leftdown));
        
        madd(ans,-1);

        root->add(y,1);
    }
    cout << ans << '\n';
}

