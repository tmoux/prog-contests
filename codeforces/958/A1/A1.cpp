#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 10;
struct SMap
{
	int size;
	char m[maxn][maxn];
	
	SMap rotate() {
		SMap ret;
		ret.size = size;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				ret.m[j][size-i-1] = m[i][j];
			}
		}
		return ret;
	}
	
	SMap flipH() {
		SMap ret;
		ret.size = size;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				ret.m[i][size-j-1] = m[i][j];
			}
		}
		return ret;
	}
	
	SMap flipV() {
		SMap ret;
		ret.size = size;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				ret.m[size-i-1][j] = m[i][j];
			}
		}
		return ret;
	}
	
	bool operator==(const SMap& rhs) const {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (m[i][j] != rhs.m[i][j]) {
					return false;
				}
			}
		}
		return true;
	}
};

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	SMap m1, m2;
	int n; cin >> n;
	m1.size = n;
	m2.size = n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> m1.m[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> m2.m[i][j];
		}
	}
	//check if same
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				if (m1 == m2) {
					cout << "Yes\n";
					return 0;
				}
				m1 = m1.flipV();
			}
			m1 = m1.flipH();
		}
		m1 = m1.rotate();
	}
	cout << "No\n";	
	return 0;
}