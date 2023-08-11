#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <set>

using namespace std;

const int maxn = 200005;
vector<int> adjacents[maxn];
vector<int> newadj[2*maxn];
int N, M;
int s;
bool visited[maxn], recStack[maxn];
int visi[2*maxn];
list<int> path, save;
bool keepGoing = true;

bool isCycleUtil(int v) {
	if (visited[v] == false) {
		visited[v] = true;
		recStack[v] = true;
		for (int i: adjacents[v]) {
			if (!visited[i] && isCycleUtil(i)) {
				return true;
			}
			else if (recStack[i]) {
				return true;
			}
		}
	}
	recStack[v] = false;
	return false;
}

void dfs(int v, list<int>& path, bool& ans) {
	//cout << v%N << '\n';
	visi[v] = true;
	path.push_back(v);
	for (int u: newadj[v]) {
		if (!visi[u]) {
			dfs(u,path,ans);
		}
	}
	if (newadj[v].size() == 0 && v/N == 1) {
		ans = true;
		save = path;
	}
	path.pop_back();
}

bool testWin() {
	list<int> path;
	bool ans = false;
	dfs(s,path,ans);
	return ans;
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		int ci; cin >> ci;
		for (int j = 1; j <= ci; j++) {
			int ai; cin >> ai; ai--;
			adjacents[i].push_back(ai);
			newadj[i].push_back(ai+N);
			newadj[i+N].push_back(ai);
		}
	}
	cin >> s;
	s--;
	bool hascycle = isCycleUtil(s);
	bool canWin = testWin();
	
	//output
	if (canWin) {
		cout << "Win\n";
		for (int i: save) {
			cout << i%N+1 << ' ';
		}
		cout << '\n';
	}
	else {
		if (hascycle) {
			cout << "Draw\n";
		}
		else {
			cout << "Lose\n";
		}
	}
	
	
	return 0;
}

