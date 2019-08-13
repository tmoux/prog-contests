#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
	int K, X; cin >> K >> X;
	for (int i = max(-1000000,X-K+1); i <= min(1000000,X+K-1); i++)
		cout << i << ' ';
	cout << '\n';
}