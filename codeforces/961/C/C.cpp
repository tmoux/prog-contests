#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 100;
int n;
bool boards[4][maxn][maxn];
pair<int,int> pi[4];

pair<int,int> getBoard(int a, int n) {
	bool par = true;
	pair<int,int> ret;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (boards[a][i][j] != par) {
				ret.first++;
			}
			par = !par;
		}
	}
	par = false;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (boards[a][i][j] != par) {
				ret.second++;
			}
			par = !par;
		}
	}
	return ret;
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	cin >> n;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < n; j++) {
			string s; cin >> s;
			for (int k = 0; k < n; k++) {
				boards[i][j][k] = (s[k] == '1');
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		pi[i] = getBoard(i,n);
	}
	/*
	for (pair<int,int> p: pi) {
		cout << p.first << ' ' << p.second << '\n';
	}
	*/
	int ans = 999999999;
	for (int i = 0; i < 4; i++) {
		for (int j = i+1; j < 4; j++) {
			int t = 0;
			for (int k = 0; k < 4; k++) {
				if (k == i || k == j) {
					t += pi[k].first;
					//cout << pi[k].first << ' ';
				}
				else {
					t += pi[k].second;
					//cout << pi[k].second;
				}
			}
			ans = min(ans,t);
		}
	}
	cout << ans << '\n';
	
	return 0;
}