/*
ID: silxikys
PROG: kimbits
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
using namespace std;
using namespace std::chrono;

#define gettime() (high_resolution_clock::now())
#define endProgram(t1) \
	fin.close(); \
 	fout.close(); \
 	cout << endl << "Execution time: " << duration_cast<nanoseconds>(gettime()-t1).count()/1000000000.0 << " seconds" << endl;
high_resolution_clock::time_point t1;

long long N, L, I; 

long long factorial(int n) {
	if (n == 0) return 1;
	return n*factorial(n-1);
}

long combinations(int n,int k) {
	if (k > n) return 0;
	return (factorial(n))/(factorial(k)*factorial(n-k));
}

unsigned long long choose(unsigned long long n, unsigned long long k) {
    if (k > n) {
        return 0;
    }
    unsigned long long r = 1;
    for (unsigned long long d = 1; d <= k; ++d) {
        r *= n--;
        r /= d;
    }
    return r;
}

long long combinate(int n,int k) {
	long sum = 0;
	for (int i = 0; i <= k;i++) {
		//cout << choose(n,i) << endl;
		sum += choose(n,i);
	}
	return sum;	
}




string ielement(long long n,long long k,long long i) {
	cout << i << endl;
	if (n == 0) {
		return "";
	}
	if (k == 0) {
		return '0'+ielement(n-1,k,i);
	}
	//if (k == 1 && n == 1 && 1 == 1) {
	//	return "1";
	//}
	int possibilities = combinate(n-1,k);
	//cout << possibilities << endl;

	if (possibilities < i) {
		//cout << n-1 << " " << k-1 << " " << i-possibilities << endl;
		cout << possibilities << " " << i << " " << i-possibilities << endl;
		return '1' + ielement(n-1,k-1,i-possibilities);
	}
	//cout << n-1 << " " << k << " "<< i << endl;
	return '0' + ielement(n-1,k,i);
}

int main() {
	t1 = gettime();
	ofstream fout("kimbits.out");
	ifstream fin("kimbits.in");

	fin >> N >> L >> I;

	string ans = ielement(N,L,I);
	cout << ans << endl;
	fout << ans << endl;

	//cout << combinate(22,19) << endl;
	

	
	endProgram(t1);
	return 0;
}