#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <unordered_map>
using namespace std;
typedef long long ll;

unordered_map<string,int> names;

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	int N; cin >> N;
	for (int i = 0; i < N; i++) {
		string s; cin >> s;
		names[s]++;
		if (names[s] == 1) {
			cout << "OK\n"; 
		}
		else {
			cout << s << (names[s]-1) << '\n';
		}
	}
	
	
	return 0;
}
