/*
ID: silxikys
PROG: vans
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <climits>
#include <array>
#include <chrono>
#include <math.h>
#include <ostream>
using namespace std;
using namespace std::chrono;

#define gettime() (high_resolution_clock::now())
#define endProgram(t1) \
	fin.close(); \
 	fout.close(); \
 	cout << endl << "Execution time: " << duration_cast<nanoseconds>(gettime()-t1).count()/1000000000.0 << " seconds" << endl;
high_resolution_clock::time_point t1;

const int maxn = 1005;
const int maxr = 4;
const int maxlen = 500;
int N;


struct Bigint
{
	vector<int> digits;
	Bigint() {}
	Bigint(int n) {
		digits.resize(maxlen,0);
		for (int i = 0; i < maxlen && n != 0; i++) {
			digits[i] = n % 10;
			n /= 10;
		}
	}

	Bigint operator+(Bigint rhs);
	Bigint operator-(Bigint rhs);
	Bigint operator*(int n);

};

Bigint f[maxn], g[maxn];

ostream& operator<<(ostream& stream, const Bigint& n) {
	int lastprint = n.digits.size() - 1;
	while (n.digits[lastprint] == 0) {
		lastprint--;
	}
	if (lastprint == -1) {
		//means number is 0
		stream << 0;
		return stream;
	}
	for (int i = lastprint; i >= 0; i--) {
		stream << n.digits[i];
	}
	return stream;
}

Bigint Bigint::operator+(Bigint rhs) {
		Bigint ret;
		vector<int> a(maxlen,0);
		ret.digits = a;
		int carry = 0;
		for (int i = 0; i < maxlen; i++) {
			ret.digits[i] = digits[i] + rhs.digits[i] + carry;
			carry = ret.digits[i] / 10;
			ret.digits[i] %= 10;
		}
		return ret;
	}

Bigint Bigint::operator-(Bigint rhs) {
	Bigint ret;
	ret.digits = digits;
	for (int i = 0; i < maxlen; i++) {
		if (ret.digits[i] < rhs.digits[i]) {
			ret.digits[i + 1]--;
			ret.digits[i] += 10;
		}
		ret.digits[i] -= rhs.digits[i];
	}
	return ret;
}

Bigint Bigint::operator*(int n) {
	Bigint ret;
	ret.digits = digits;
	int carry = 0;
	for (int i = 0; i < maxlen; i++) {
		ret.digits[i] = ret.digits[i] * n + carry;
		carry = ret.digits[i] / 10;
		ret.digits[i] %= 10;
	}
	return ret;

}

int main() {
	t1 = gettime();
	ofstream fout("vans.out");
	ifstream fin("vans.in");
	
	fin >> N;
	g[1] = Bigint(2);
	g[2] = Bigint(2);
	g[3] = Bigint(8);
	f[1] = Bigint(0);
	f[2] = Bigint(2);
	f[3] = Bigint(4);

	for (int i = 4; i <= N; i++) {
		g[i] = f[i-1]*2 + g[i-1] + g[i-2] - g[i-3];
		f[i] = f[i-1] + g[i-1];
	}
	
	cout << f[N] << '\n';
	fout << f[N] << '\n';
	
	

	

	endProgram(t1);
	return 0;
}