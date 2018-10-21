#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <map>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 5005;
int n;
int A[maxn], sol[maxn];
bool seen[maxn];
map<int,int> mp;

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    int idx = 0;
    int zero = -1;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
        bool isNeg = A[i] < 0;
        if (isNeg) A[i] *= -1;
        for (int j = 2; j*j <= A[i]; j++) {
            while (A[i]%(j*j)==0) A[i] /= (j*j);
        }
        if (isNeg) A[i] *= -1;
        if (mp.find(A[i]) == mp.end()) mp[A[i]] = idx++;
        if (A[i] == 0) zero = mp[A[i]];
        A[i] = mp[A[i]];
    }

   
    for (int i = 0; i < n; i++) {
        memset(seen,0,sizeof(seen));
        int sz = 0;
        for (int j = i; j < n; j++) {
            if (A[j] != zero && !seen[A[j]]) {
                seen[A[j]] = true;
                sz++;
            }
            sol[max(sz,1)]++;
            //cout << sz << '\n';
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << sol[i] << (i < n ? ' ' : '\n');
    }
    return 0;
}
	

