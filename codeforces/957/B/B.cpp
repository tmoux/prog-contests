#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int,int> pii;
#include <set>

string grid[50];
int colored[50][50];

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	int n, m; cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> grid[i];
	}
	bool canMake = true;
	for (int i = 0; i < n; i++) {
		vector<int> marked;
		for (int j = 0; j < m; j++) {
			if (grid[i][j] == '#') {
				marked.push_back(j);
			}
		}
		for (int k = 0; k < n; k++) {
			int numMarked = 0;
			for (int j: marked) {
				if (grid[k][j] == '#') {
					numMarked++;
				}
			}
			if (numMarked != 0 && numMarked != marked.size()) {
				canMake = false;
				break;
			}
		}
	}
	
	string ans = (canMake) ? "Yes" : "No";
	cout << ans << '\n';
	
	
	return 0;
}

