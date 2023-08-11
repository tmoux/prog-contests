#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

int N, A, B;
const int maxn = 1000005;
int permute[maxn];

void addPermute(int idx, int num) {
	for (int i = 0; i < num; i++) {
		permute[i+idx] = ((i+num-1) % num) + idx; 
	}
}

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	cin >> N >> A >> B;
	for (int i = 0; A*i <= N; i++) {
		if ((N-A*i) % B == 0) {
			int numA = i;
			int numB = (N-A*i)/B;
			for (int j = 0; j < numA; j++) {
				addPermute(1+j*A,A);
			}
			for (int j = 0; j < numB; j++) {
				addPermute(1+A*numA+j*B,B);
			}
			for (int i = 1; i <= N; i++) {
				cout << permute[i] << ' ';
			}
			cout << '\n';
			return 0;
		}
	}
	cout << "-1\n";	
	
	return 0;
}
