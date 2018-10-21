/*
ID: silxikys
PROG: cowroute
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

ofstream fout("cowroute.out");
ifstream fin("cowroute.in");

struct Route
{
	long long cost;
	vector<int> cities;
};
struct Pack
{
	long long cost;
	int numCities;
};

const int maxn = 1001;
int A, B, N;
vector<Route> routes[maxn];
Pack dp[maxn];

Pack f(int i) {
	if (dp[i].cost != -1) {
		return dp[i];
	}
	if (i == B) {
		return dp[i] = {0,1};
	}
	for (Route r: routes[i]) {
		for (int stop = 1; stop < r.cities.size(); stop++) {
			Pack nextStop = f(r.cities[stop]);
			if (nextStop.cost != -1) {
				Pack tr = {r.cost + nextStop.cost, 1 + nextStop.numCities};
				if (dp[i].cost == -1 || dp[i].cost > tr.cost) {
					dp[i] = tr;
					//cout << stop << '\n';
					//cout << dp[i].cost << ' ' << dp[i].numCities << '\n';
				}
			}
			
		}
	}
	return dp[i];
}

int main() 
{
	fin >> A >> B >> N;
	for (int i = 0; i < maxn; i++) {
		dp[i] = {-1,-1};
	}
	for (int i = 0; i < N; i++) {
		int cost, numcities; fin >> cost >> numcities;
		vector<int> toadd;
		for (int j = 0; j < numcities; j++) {
			int a; fin >> a;
			toadd.push_back(a);
		}
		routes[toadd[0]].push_back({cost,toadd});
	}
	/*
	for (int i = 1; i <= 5; i++) {
		cout << i << '\n';
		for (Route r: routes[i]) {
			for (int i: r.cities) {
				cout << i << ' ';
			}
			cout << '\n';
		}
		cout << '\n';
	}
	*/

	
	Pack p = f(A);
	cout << p.cost << ' ' << p.numCities << '\n';
	fout << p.cost << ' ' << p.numCities << '\n';
	/*
	for (int i = 1; i <= 5; i++) {
		cout << i << ' ' << dp[i].cost << ' ' << dp[i].numCities << '\n';
	}
	*/
	




	return 0;
}