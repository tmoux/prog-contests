#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 200005;
int BIT[maxn], A[maxn];
int n;

void modify(int j, int n) { for (; j <= n; j += (j&-j)) BIT[j]++;}
int prefix_sum(int j) { int sum = 0; for (; j > 0; j -= (j & -j)) sum += BIT[j]; return sum;}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    int ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        ans += prefix_sum(A[i]);
        modify(A[i],n);
        cout << ans << '\n';
    }
    


    return 0;
}
	

