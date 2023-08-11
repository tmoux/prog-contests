#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstring>
using namespace std;

ofstream fout("output.txt");
ifstream fin("input.txt");

const int maxn = 100005;
int n, A[maxn];

int main() 
{
    fin >> n;
    for (int i = 0; i < n; i++) {
        fin >> A[i];
    }
    sort(A,A+n);
    int *left = A, *right = A;
    while (*right <= *left * 2) {
        ++right;
        if (right == A + n) break;
    }
    int ans = n - (distance(left,right));
    for (++left; left != A + n; ++left) {
        if (right == A + n) continue;
        while (*right <= *left * 2) {
            ++right;
            if (right == A + n) break;
        }
        ans = min(ans,(int)(n - (distance(left,right))));
    }

    fout << ans << '\n';

	return 0;
}

