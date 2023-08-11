#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;

struct pt
{
	ll x,y;
};
bool operator==(const pt& lhs, const pt& rhs) {
	return lhs.x == rhs.x && lhs.y == rhs.y;
}
const int maxn = 100005;
int N;
pt A[maxn];
bool avai[maxn];

bool isCollin(pt A, pt B, pt C) {
	return (A == B || A == C) || (A.y-B.y)*(C.x-B.x) == (A.x-B.x)*(C.y-B.y);
}

bool doCheck(pt p1, pt p2) {
	memset(avai,0,sizeof(avai));
	for (int i = 0; i < N; i++) {
		if (isCollin(A[i],p1,p2)) {
			avai[i] = true;
		}
	}
	vector<pt> others;
	bool flag = true;
	for (int i = 0; i < N; i++) {
		if (!avai[i]) {
			if (others.size() < 2) {
				others.push_back(A[i]);
			}
			else {
				if (!isCollin(A[i],others[0],others[1])) {
					flag = false;
				}
			}
		}
	}
	return flag;
}

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	cin >> N;
	for (int i = 0; i < N; i++) {
		ll x, y; cin >> x >> y;
		A[i] = {x,y};
	}
	if (N <= 4) {
		cout << "YES\n";
		return 0;
	}
	if (doCheck(A[0],A[1]) || doCheck(A[1],A[2]) || doCheck(A[0],A[2])) {
		cout << "YES\n";
	}
	else {
		cout << "NO\n";
	}
	
	
	return 0;
}