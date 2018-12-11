#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 105;
int N, A[maxn][maxn];

int Solve() {
	int x = 1, y = 1, sx = 0, sy = 0;
	for (int i = 2; i <= N; i++) {
		if (sx + A[x][i] < sy + A[y][i]) {
			sx += A[x][i];
			x = i;
		}
		else {
			sy += A[y][i];
			y = i;
		}
	}
	return sx + sy;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for (int i = 1; i < N; i++) {
    	for (int j = i+1; j <= N; j++) {
    		cin >> A[i][j];
    	}
    }
    cout << Solve() << '\n';
    return 0;
}