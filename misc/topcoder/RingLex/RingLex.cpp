#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

bool isPrime(int n) {
	for (int i = 2; i < n; i++) {
		if (n % i == 0) return false;
	}
	return true;
}

string buildString(const string& s, int x, int p) {
	string ret = "";
	int n = s.size();
	for (int i = 0; i < n; i++) {
		ret += s[(x+i*p)%n];
	}
	return ret;
}

string getmin(string s) {
	vector<string> rets;
	vector<int> primes;
	for (int i = 2; i < s.size(); i++) {
		if (isPrime(i)) primes.push_back(i);
	}
	for (int x = 0; x < s.size(); x++) {
		for (int p: primes) {
			string built = buildString(s,x,p);
			rets.push_back(built);
		}
	}
	sort(rets.begin(),rets.end());
	return rets[0];
}

int main()
{
	cout << getmin("abbaac") << '\n';
	
	return 0;
}