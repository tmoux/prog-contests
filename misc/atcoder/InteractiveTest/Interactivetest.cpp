#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;



int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	int N, Q; cin >> N >> Q;
	string s;
	for (int i = 0; i < N; i++) {
		s += (char)('A'+i);
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N-1; j++) {
			cout << "? " << s[j] << ' ' << s[j+1] << endl;
			char ans;
			cin >> ans;
			if (ans == '>') {
				swap(s[j],s[j+1]);
			}
		}
	}
	cout << "! " << s << endl;
	
	
	return 0;
}