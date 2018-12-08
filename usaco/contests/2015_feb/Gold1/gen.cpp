#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
	int R, C; cin >> R >> C;
	printf("%d %d %d\n",R,C,R*C);
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cout << (rand() % (R*C)) + 1 << ' ';
		}
		cout << '\n';
	}


    return 0;
}