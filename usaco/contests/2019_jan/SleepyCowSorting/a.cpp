#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5+5;
int N, a[maxn];

int bit[maxn];
void add(int i, int x) {
    for (; i <= N; i += i & (-i))
        bit[i] += x;
}

int sum(int i) {
    int r = 0;
    for (; i; i -= i & (-i)) {
        r += bit[i];
    }
    return r;
}

int main()
{
	freopen("sleepy.in","r",stdin); freopen("sleepy.out","w",stdout);
	cin >> N;
	for (int i = 1; i <= N; i++) cin >> a[i];
	int L = N;
	add(a[L],1);
	
	while (L > 1 && a[L-1] < a[L]) {
		add(a[--L],1);
	}
	int ol = L;
	vector<int> ans;
	for (int i = 1; i < ol; i++) {
		int g = sum(a[i]) + L - 2;
		add(a[i],1);
		//cout << g << endl;
		L--;
		if (!g) break;
		ans.push_back(g);
	}
	//output
	cout << ans.size() << '\n';
	for (int i = 0; i < ans.size(); i++) {
		cout << ans[i];
		if (i != ans.size() - 1) {
			cout << ' ';
		}
		else cout << '\n';
	}
}