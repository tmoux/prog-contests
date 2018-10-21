/*
ID: silxikys
PROG: hayfeast
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
#include <queue>
using namespace std;

ofstream fout("hayfeast.out");
ifstream fin("hayfeast.in");

const int maxn = 100000;
int N, M;

int flavor[maxn];
pair<int,int> haybales[maxn];
pair<int,priority_queue<int>> val[maxn];

int main() 
{
	fin >> N >> M;
	for (int i = 0; i < N; i++) {
		int f, s;
		fin >> f >> s;
		haybales[i] = make_pair(f,s);
		if (i == 0) {
			flavor[i] = f;
		}
		else {
			flavor[i] = flavor[i-1] + f;
		}
	}

	int minspicy = 2000000000;
	int index = 0;
	priority_queue<int> firsti;
	for (; index < N; index++) {
		firsti.push(haybales[index].second);
		if (flavor[index] >= M) {
			break;
		}	
	}
	
	val[0] = make_pair(index,firsti);
	/*
	cout << val[0].first << '\n';
	while (!val[0].second.empty()) {
		cout << val[0].second.top() << '\n';
		val[0].second.pop();
	}
	*/
	priority_queue<int> emptyyy;

	for (int i = 1; i < N; i++) {
		
		int totalflavor = flavor[val[i-1].first] - flavor[i-1];
		int newindex = val[i-1].first;
		priority_queue<int> toadd = val[i-1].second;
		
		if (totalflavor < M) {
			int j = val[i-1].first+1;
			for (; j < N && totalflavor < M; j++) {
				totalflavor = flavor[j] - flavor[i-1];
				toadd.push(haybales[j].second);
			}
			newindex = j;
		}

		else {
			int j = i;
			totalflavor = 0;
			toadd = emptyyy;
			for (; j < N; j++) {
				toadd.push(haybales[j].second);
				if (flavor[j]-flavor[i-1] >= M) {
					break;
				}
			}
			newindex = j;
		}
		
		val[i] = make_pair(newindex,toadd);
		//cout << val[i].first << ' ' << val[i].second.top() << '\n';
	}
	
	for (int i = 0; i < N; i++) {
		//cout << val[i].first << ' ' << val[i].second.top() << '\n';
		minspicy = min(minspicy,val[i].second.top());
	}

	cout << minspicy << '\n';
	fout << minspicy << '\n';
	

	return 0;
}