#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <set>
using namespace std;
typedef long long ll;

int n;
const int maxn = 905;
const int msb = 16;
int A[maxn], pfx[maxn];
struct Node
{
	Node* child[2];
	int val;
	int maxl;
	int minr;
};

Node* newNode() {
	Node* ret = new Node();
	for (int i = 0; i < 2; i++) {
		ret->child[i] = NULL;
	}
	ret->val = -1;
	ret->maxl = 1;
	ret->minr = n;
	return ret;
}

void addSum(Node* curr, int s, pair<int,int> lr) {
	curr->maxl = max(curr->maxl,lr.first);
	curr->minr = min(curr->minr,lr.second);
	for (int i = msb; i >= 0; i--) {
		bool nxt = s&(1<<i);
		if (curr->child[nxt] == NULL) {
			curr->child[nxt] = newNode();
		}
		curr = curr->child[nxt];
		curr->maxl = max(curr->maxl,lr.first);
		curr->minr = min(curr->minr,lr.second);
	}
	curr->val = s;
}

bool isValid(Node* curr, const pair<int,int>& lr) {
	return (lr.first > curr->minr || lr.second < curr->maxl);
}

int query(Node* curr, int s, pair<int,int> lr) {
	//cout << curr->maxl << ' ' << curr->minr << ' ' << isValid(curr,lr) << '\n';
	for (int i = msb; i>= 0; i--) {
		bool nxt = !(s&(1<<i));
		if (curr->child[nxt] == NULL || (!isValid(curr->child[nxt],lr))) {
			nxt = !nxt;
		}
		curr = curr->child[nxt];
		//cout << curr->maxl << ' ' << curr->minr << ' ' << isValid(curr,lr) << '\n';
	}
	//now at leaf
	return s^curr->val;
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	freopen("input.in","r",stdin);
	cin >> n;
	Node* root = newNode();
	for (int i = 1; i <= n; i++) {
		cin >> A[i];
		pfx[i] = pfx[i-1] + A[i];
	}

	for (int i = 0; i < n; i++) {
		for (int j = i+1; j <= n; j++) {
			int sum = pfx[j]-pfx[i];
			addSum(root,sum, {i+1,j});
		}
	}
	
	int ans = 0;
	
	for (int i = 0; i < n; i++) {
		for (int j = i+1;  j <=n; j++) {
			int sum = pfx[j]-pfx[i];
			int maxQuery = query(root,sum, {i+1,j});
			ans = max(ans,maxQuery);
		}
	}
	
	//int maxQuery = query(root,A[1]+A[2]+A[3],{1,3});
	//cout << maxQuery << '\n';
	
	
	cout << ans << '\n';
	return 0;
}