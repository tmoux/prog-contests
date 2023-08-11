#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

const int maxn = 100005;
int N;
int arr[maxn];
int compress[3];
int compare1[3], compare2[3];
int saveSeq[3];

int computeNumEq(int a1[3], int a2[3]) {
	return min(a1[0],a2[0]) + min(a1[1],a2[1]) + min(a1[2],a2[2]);
}

void arrCopy(int* arr1, int* arr2) {
	for (int i = 0; i < 3; i++) {
		arr2[i] = arr1[i];
	}
}

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	cin >> N;
	int minnum, maxnum;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
		if (i == 0) {
			minnum = arr[i];
			maxnum = arr[i];
		}
		else {
			minnum = min(minnum,arr[i]);
			maxnum = max(maxnum,arr[i]);
		}
	}
	if (maxnum-minnum < 2) {
		//ans is the same
		cout << N << '\n';
		for (int i = 0; i < N; i++) {
			cout << arr[i];
			if (i != N-1) cout << ' ';
		}
		cout << '\n';
		return 0;
	}
	for (int i = 0; i < N; i++) {
		compress[arr[i]-minnum]++;
		compare1[arr[i]-minnum]++;
		compare2[arr[i]-minnum]++;
	}
	int minAns = N;
	arrCopy(compress,saveSeq);
	while (compare1[1] > 1) {
		compare1[1] -= 2;
		compare1[0]++;
		compare1[2]++;
		if (computeNumEq(compress,compare1) < minAns) {
			minAns = computeNumEq(compress,compare1);
			arrCopy(compare1,saveSeq);
		}
	}
	while (compare2[0] > 0 && compare2[2] > 0) {
		//cout << compare2[0] << ' ' << minAns << '\n';
		compare2[0]--;
		compare2[2]--;
		compare2[1] += 2;
		if (computeNumEq(compress,compare2) < minAns) {
			minAns = computeNumEq(compress,compare2);
			arrCopy(compare2,saveSeq);
		}
	}
	
	cout << minAns << '\n';
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < saveSeq[i]; j++) {
			cout << i+minnum;
			if (i != 2 || j != saveSeq[i]-1) {
				cout << ' ';
			}
		}
	}
	cout << '\n';
	
	
	
	
	
	return 0;
}

