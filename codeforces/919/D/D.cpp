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
	//now we know that the graph is acyclic, perform bfs
	//create queue of all leafs
	vector<int> leafs;
	for (int i = 1; i <= N; i++) {
		if (adjacents[i].empty()) {
			leafs.push_back(i);
		}
	}
	//for each letter 0-25, bfs from the leafs and fill in to the roots, then find max value for all nodes
	for (int letter = 0; letter < alphsize; letter++) {
		queue<int> lfs;
		for (int i: leafs) {
			lfs.push(i);
			maxletter[i][letter] = 0;
			if (label[i] == letter) maxletter[i][letter]++;
		}
		while (!lfs.empty()) {
			int f = lfs.front();
			for (int i: reverses[f]) {
				if (maxletter[i][letter] <= maxletter[f][letter]) {
					maxletter[i][letter] = maxletter[f][letter];
					if (label[i] == letter) maxletter[i][letter]++;
					lfs.push(i);
				}
			}
			lfs.pop();  
		}
	}
	
	int largestValue = -1;
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < alphsize; j++) {
			largestValue = max(largestValue, maxletter[i][j]);
		}
	}
	cout << largestValue << '\n';
	
	
	
	
	
	return 0;
}
