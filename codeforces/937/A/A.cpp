#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 101;
int scores[maxn];
int N;
int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> scores[i];
	}
	sort(scores,scores+N);
	int prev = -1;
	int ans = 0;
	for (int i = 0; i < N; i++) {
		if (scores[i] != 0 && scores[i] != prev) {
			ans++;
		}
		prev = scores[i];
	}
	cout << ans << '\n';
	
	
	return 0;
}

