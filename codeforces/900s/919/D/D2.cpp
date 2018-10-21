#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
using namespace std;

const int maxn = 300001;
const int alphsize = 26;
int label[maxn];
set<int> adjacents[maxn];
set<int> reverses[maxn];
int maxletter[maxn][alphsize];
//maxletter[i][j] gives the maximum number of letter j that appears in the subtree rooted at node i
int N, M;

bool visited[maxn], recStack[maxn];
ifstream fin("D.in");

bool isCycleUtil(int v) {
	if (visited[v] == false) {
		visited[v] = true;
		recStack[v] = true;
		set<int>::iterator i;
		for (i = adjacents[v].begin(); i != adjacents[v].end(); ++i) {
			if (!visited[*i] && isCycleUtil(*i)) {
				return true;
			}
			else if (recStack[*i]) {
				return true;
			}
		}
	}
	recStack[v] = false;
	return false;
}

bool isCyclic() {
	for (int i = 1; i <= N; i++) {
		if (isCycleUtil(i)) {
			return true;
		}
	}
	return false;
}

int findMax(int i, int letter) {
	if (maxletter[i][letter] != -1) {
		return maxletter[i][letter];
	}
	int isLetter = label[i] == letter ? 1 : 0;
	int maxSubtree = 0;
	for (int j: adjacents[i]) {
		maxSubtree = max(maxSubtree,findMax(j,letter));
	}
	return maxletter[i][letter] = isLetter + maxSubtree;
}

int main()
{
	cin >> N >> M;
	for (int i = 0; i < maxn; i++) {
		for (int j = 0; j < alphsize; j++) {
			maxletter[i][j] = -1;
		}
	}
	string s; cin >> s;
	for (int i = 0; i < N; i++) {
		label[i+1] = s[i]-'a';
	}
	for (int i = 0; i < M; i++) {
		int x, y; cin >> x >> y;
		adjacents[x].insert(y);
		reverses[y].insert(x);
	}
	//detect cycles, if there is one, return -1
	if (isCyclic()) {
		cout << "-1\n";
		return 0;
	}
	//identify all roots
	vector<int> roots;
	for (int i = 1; i <= N; i++) {
		if (reverses[i].empty()) {
			roots.push_back(i);
		}
	}
	
	int maxValue = -1;
	for (int letter = 0; letter < alphsize; letter++) {
		for (int i: roots) {
			maxValue = max(maxValue,findMax(i,letter));
		}
	}	
	cout << maxValue << '\n';
	
	
	
	
	
	return 0;
}
