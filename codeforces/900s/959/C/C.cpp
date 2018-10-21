#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;



int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	int N; cin >> N;
	//build incorrect one
	if (N < 6) {
		cout << "-1\n";
	}
	else {
		cout << "1 2\n1 3\n1 4\n4 5\n4 6\n";
		for (int i = 7; i <= N; i++) {
			cout << "4 " << i << '\n';
		}
	}
	//build correct one
	for (int i = 1; i < N; i++) {
		cout << i << ' '  << i+1 << '\n';
	}
	
	return 0;
}

