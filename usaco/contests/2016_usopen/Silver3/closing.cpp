/*
ID: silxikys
PROG: closing
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

ofstream fout("closing.out");
ifstream fin("closing.in");

int N, M;
const int maxn = 3001;
vector<int> adjacents[maxn];

void floodfill(int& count, bool visited[], int i) {
	visited[i] = true;
	count++;
	for (int adj: adjacents[i]) {
		if (!visited[adj]) {
			floodfill(count, visited, adj);
		}
	}
}

int main() 
{
	fin >> N >> M;
	for (int i = 0; i < M; i++) {
		int a, b; fin >> a >> b;
		adjacents[a].push_back(b);
		adjacents[b].push_back(a);
	}

	int firstCount = 0;
	bool visi[maxn] = {false};
	for (int i = 1; i <= N; i++) {
		visi[i] = false;
	}
	floodfill(firstCount,visi,1);
	if (firstCount == N) {
		cout << "YES" << '\n';
		fout << "YES" << '\n';
	}
	else {
		cout << "NO" << '\n';
		fout << "NO" << '\n';
	}

	bool alive[maxn];
	for (int i = 1; i <= N; i++) {
		alive[i] = true;
	}
	for (int i = 0; i < N - 1; i++) {
		int a; fin >> a;
		//delete a from adjacent lists
		for (int j = 1; j <= N; j++) {
			adjacents[j].erase(remove(adjacents[j].begin(),adjacents[j].end(),a),adjacents[j].end());
		}
		alive[a] = false;
		int counter = 0;
		/*
		for (int i = 1; i <= N; i++) {
			cout << alive[i] << ' ';
		} cout << '\n';
		*/
		bool visis[maxn] = {false};
		for (int i = 1; i <= N; i++) {
			visis[i] = false;
		}
		for (int as = 1; as <= N; as++) {
			//cout << as << ' ' << alive[as] << '\n';
			if (alive[as]) {
				floodfill(counter,visis,as);
				//cout << counter << '\n';
				break;
			}
			
		
		}

		if (counter == N - i - 1) {
			cout << "YES" << '\n';
			fout << "YES" << '\n';
		}
		else {
			cout << "NO" << '\n';
			fout << "NO" << '\n';
		}
	}






	return 0;
}