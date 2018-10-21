#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 1505;
int BIT[maxn], A[maxn];
int n, m;

void modify(int j, int n) { for (; j <= n; j += (j&-j)) BIT[j]++;}
int prefix_sum(int j) { int sum = 0; for (; j > 0; j -= (j & -j)) sum += BIT[j]; return sum;}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    int numInv = 0;
    for (int i = n - 1; i >= 0; i--) {
        numInv += prefix_sum(A[i]);
        modify(A[i],n);
    }
    numInv %= 2;
    cin >> m;
    while (m--) {
        int li, ri; cin >> li >> ri;
        if ((ri-li+1) % 4 >= 2) {
            numInv ^= 1;
        }
        cout << (numInv ? "odd" : "even") << '\n';
    }
    


    return 0;
}
	

