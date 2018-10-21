#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

const int maxn = 200005;
int n, a, b;
char train[maxn];
vector<int> invls;
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	cin >> n >> a >> b;
	int a1 = a, b1 = b;
	int tot = 0;
	for (int i = 0; i < n; i++) {
		cin >> train[i];
		if (train[i] == '.') tot++;
	}
	train[n] = '*';
	for (int i = 0; i < n;) {
		if (train[i] == '*') {
			i++;
			continue;
		}
		else {
			int l = i;
			while (train[i] == '.') {
				i++;
			}
			int r = i-1;
			invls.push_back(r-l+1);
		}
	}
	//sort(invls.begin(),invls.end(),greater<int>());
	for (int len: invls) {
		int n1 = (len % 2 == 0) ? len/2 : len/2+1;
		int n2 = len/2;
		if (b > a) swap(a,b);
		a = max(0,a-n1);
		b = max(0,b-n2);
	}
	int ans = (a1-a)+(b1-b);
	cout << ans << '\n';
	
	
	
	return 0;
}