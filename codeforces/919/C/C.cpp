#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

const int maxn = 2001;
string grid[maxn];
map<char,int> mapping = {{'*',0},{'.',1}};
int main()
{
	int n, m, k; cin >> n >> m >> k;
	int nways = 0;
	for (int i = 0; i < n; i++) {
		cin >> grid[i];
		int curr = 0;
		for (int j = 0; j < m; j++) {
			if (grid[i][j] == '*') {
				curr = 0;
			}
			else {
				curr++;
			}
			if (curr >= k) {
				nways++;
			}
		}
	}
	if (k != 1) {
		int numways = nways;
			//count cols
			for (int j = 0; j < m; j++) {
				int curr = 0;
				for (int i = 0; i < n; i++) {
					if (grid[i][j] == '*') {
						curr = 0;
					}
					else {
						curr++;
					}
					if (curr >= k) {
						numways++;
					}
				}
			}
			cout << numways << '\n';
	}
	else {
		int numways = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (grid[i][j] == '.') {
					numways++;
				}
			}
		}
		cout << numways << '\n';
	}
	
	
	return 0;
}
