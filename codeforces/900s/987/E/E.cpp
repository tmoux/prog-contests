#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <unordered_map>
using namespace std;
typedef long long ll;

const int maxn = 1000006;
int n, A[maxn], orig[maxn];
unordered_map<int,int> mp;

void sw(int i, int j) {
    int iIdx = mp[i], jIdx = mp[j];
    swap(orig[iIdx],orig[jIdx]);
    swap(mp[i],mp[j]);
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
    }
    for (int i = 1; i <= n; i++) {
        orig[i] = i;
        mp[i] = i;
    }
    int numSwitch = 0;
    for (int i = 1; i <= n; i++) {
        if (orig[i] != A[i]) {
            sw(orig[i],A[i]);
            numSwitch++;
        }
    }
    //cout << numSwitch << '\n';
    bool a = (n & 1), b = (numSwitch & 1);
    cout << (a ^ b ? "Um_nik" : "Petr") << '\n';

    return 0;
}
	

