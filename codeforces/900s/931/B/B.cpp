#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <math.h>
using namespace std;



int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	int n, a, b;
	cin >> n >> a >> b;
	vector<int> teams;
	for (int i = 1; i <= n; i++) {
		teams.push_back(i);
	}
	int round = 1;
	bool notFound = true;
	while (teams.size() > 1 && notFound) {
		/*
		for (int i: teams) {
			cout << i << ' ';
		}
		cout << '\n';'
		*/
		vector<int> newvec;
		for (int i = 0; i < teams.size()/2; i++) {
			int first = teams[i*2];
			int second = teams[i*2+1];
			if ((first == a || first == b) && (second == a || second == b)) {
				notFound = false;
			}
			else {
				if (second == a || second == b) {
					newvec.push_back(second);
				}
				else {
					newvec.push_back(first);
				}
			}
		}
		teams = newvec;
		if (notFound) {
			round++;
		}
		
	}
	
	//output
	int maxrounds = (int)log2(n);
	//cout << maxrounds << '\n';
	if (round != maxrounds) {
		cout << round << '\n';
	}
	else {
		cout << "Final!\n";
	}	
	
	return 0;
}

