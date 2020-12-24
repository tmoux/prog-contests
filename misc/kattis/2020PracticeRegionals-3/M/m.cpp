#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Node {
	int s, e, m;
	//covers s,e;
	int sum;
	int maxi;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		sum = 0;
		maxi = 0;
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
      sum = max(sum,x);
			maxi = sum;
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
		maxi = max(l->maxi,r->maxi);
	}

	int getmaxi(int st, int en) {
		if (st <= s && e <= en) {
			return maxi;
		}
		int ret = 0;
		if (st <= m) {
			ret = max(ret,l->getmaxi(st,en));
		}
		if (en > m) {
			ret = max(ret,r->getmaxi(st,en));
		}
		return ret;
	}	

	int getsum(int st, int en) {
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

const int maxn = 1e5+5;
int n;
int x[maxn], y[maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n;
  int xh, yh, xw, yw; 
  cin >> xh >> yh >> xw >> yw;
  xw -= xh;
  yw -= yh;
  for (int i = 0; i < n; i++) {
    cin >> x[i] >> y[i];
    x[i] -= xh;
    y[i] -= yh;
  }
  //flip everything so (xw,yw) is positive
  for (int i = 0; i < n; i++) {
    if (xw < 0) x[i] *= -1;
    if (yw < 0) y[i] *= -1;
  }
  x[n] = abs(xw);
  y[n] = abs(yw);

  map<int,int> compress;
  vector<int> ys = {0};
  for (int i = 0; i <= n; i++) {
    ys.push_back(y[i]);
  }
  sort(ys.begin(),ys.end());
  int pt = 0;
  for (auto i: ys) {
    if (!compress.count(i)) {
      compress[i] = pt++;
    }
  }

  vector<pair<pair<int,int>,int>> points;
  for (int i = 0; i <= n; i++) {
    y[i] = compress[y[i]];
    points.push_back({{x[i],y[i]},i});
  }
  sort(points.begin(),points.end());

  Node *root = new Node(0,pt);
  for (auto p: points) {
    int X = p.first.first;
    int Y = p.first.second;
    int id = p.second;
    //cout << X << ' ' << Y << endl;
    if (X < 0 || Y < compress[0]) continue;
    int dp = root->getmaxi(compress[0],Y) + 1;
    root->add(Y,dp);
    if (id == n) {
      cout << dp-1 << '\n';
      return 0;
    }
  }
  assert(false);
}

