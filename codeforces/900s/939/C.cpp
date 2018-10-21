#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 100002;
int n;
int numPeople[2*maxn];

int mod(int n, int mod) {
	while (n < 0) {
		n += mod;
	}
	n %= mod;
	if (n == 0) return mod;
	return n;
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> numPeople[i];
		numPeople[i+n] = numPeople[i];
	}
	int s, f; cin >> s >> f;
	//if (f < s) f += n;
	int curr = 0, maxSum = -1, startingTime;
	int intervalLength = f - s;
	for (int i = s; i < f; i++) {
		curr += numPeople[i];
	}
	maxSum = curr;
	startingTime = 1;
	for (int i = 1; i < n; i++) {
		curr += numPeople[f + i - 1];
		curr -= numPeople[s + i - 1];
		if (curr > maxSum || (curr == maxSum && mod(1-i,n) < startingTime)) {
			maxSum = curr;
			startingTime = mod(1 - i,n);
		}
		//cout << i << ' ' << curr << ' ' << startingTime << ' ' << '\n';
	}
	cout << startingTime << '\n';
	
	
	
	return 0;
}
