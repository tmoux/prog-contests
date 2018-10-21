#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;
const ll maxn = 2000000000000000000; //2*10^18
const int maxk = 100001;

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	ll N; int K; cin >> N >> K;
	ll minResidue = maxn, boxType, numBoxes;
	for (int i = 1; i <= K; i++) {
		ll ak; cin >> ak;
		if (N % ak < minResidue) {
			minResidue = N % ak;
			boxType = i;
			numBoxes = N/ak;
		}
	}
	cout << boxType << ' ' << numBoxes << '\n';
	
	
	return 0;
}
