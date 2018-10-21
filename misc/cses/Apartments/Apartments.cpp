#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 200005;
int N, M, K, ai, bi;
int requests[maxn], houses[maxn];

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		cin >> requests[i];
	}
	for (int i = 0; i < M; i++) {
		cin >> houses[i];
	}
	sort(requests,requests+N);
	sort(houses,houses+M);
	/*
	for (int i = 0; i < N; i++) cout << requests[i] << ' ';
	cout << '\n';
	for (int i = 0; i < M; i++) cout << houses[i] << ' ';
	cout << '\n';
	*/
	int ans = 0;
	int idx = 0;
	for (int i = 0; i < M; i++) {
		int house = houses[i];
		while (requests[idx] < house-K && idx < N) {idx++;}
		if (house-K <= requests[idx] && requests[idx] <= house+K) {
			ans++;
			idx++;
		}
	}
	cout << ans << '\n';
	
	return 0;
}

