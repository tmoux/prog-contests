#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <math.h>
using namespace std;
typedef long long ll;

class CubeStackingGame
{
public:
int maxVal = 1;
void dfs(int curstack[10][4], int n, const vector<vector<int>>& colors, int maxn) {
	if (n == maxn) {
		return;
	}
	

	for (int i = 0; i < 4; i++) {
        bool isValid = true;
		for (int j = 0; j < 4; j++) {
			curstack[n][(i+j)%4] = colors[j][n];
            int lastAdded = colors[j][n];
            for (int k = 0; k < n; k++) {
				if (curstack[k][(i+j)%4] == lastAdded) {
					isValid = false;
					break;
				}
			}
		}

		if (isValid) {
            maxVal = max(maxVal,n+1);
            dfs(curstack,n+1,colors,maxn);
        }
		
	}

	for (int i = 0; i < 4; i++) {
        bool isValid = true;
		for (int j = 0; j < 4; j++) {
			curstack[n][3-((i+j)%4)] = colors[j][n];
            int lastAdded = colors[j][n];
            for (int k = 0; k < n; k++) {
				if (curstack[k][3-((i+j)%4)] == lastAdded) {
					isValid = false;
					break;
				}
			}
		}
		for (int j = 0; j < 4; j++) {
			cout << 3-((i+j)%4) << ' ';
		}

		if (isValid) {
            maxVal = max(maxVal,n+1);
            dfs(curstack,n+1,colors,maxn);
        }
		
	}
}
int MaximumValue(int n, vector<int> c1, vector<int> c2, vector<int> c3, vector<int> c4) {
	vector<vector<int>> colors = {c1,c2,c3,c4};
	int curstack[10][4];
	curstack[0][0] = c1[0];
	curstack[0][1] = c2[0];
	curstack[0][2] = c3[0];
	curstack[0][3] = c4[0];

	dfs(curstack, 1, colors, n);
	return maxVal;
}
};

int main()
{
	CubeStackingGame c;
	cout << c.MaximumValue(4,{1,1,1,1},{2,2,2,2},{3,3,3,3},{4,4,4,2}) << '\n';
}