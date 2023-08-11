#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


int findSide(int x, int y, int curr) {
	if (x > y) return 1;
	if (x < y) return 2;
	if (x == y) return curr;
}

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	int N; cin >> N;
	int xpos = 0, ypos = 0;
	int currSide = 0;
	string s; cin >> s;
	int numCoins = 0;
	for (int i = 0; i < N; i++) {
		char c = s[i];
		if (c == 'R') {
			xpos++;
		}
		if (c == 'U') {
			ypos++;
		}
		if (findSide(xpos,ypos, currSide) != currSide && i != 0) {
			numCoins++;
		}
		currSide = findSide(xpos,ypos,currSide);
		//cout << numCoins << '\n';
	}
	cout << numCoins << '\n';
	
	
	return 0;
}

