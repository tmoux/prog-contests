#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

struct Operation {int l, r; ll d;};
const int maxn = 100005;
int n, m, k;
ll A[maxn], pre[maxn], agg[maxn];
Operation ops[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        cin >> A[i+1]; 
    }
    for (int i = 1; i <= m; i++) {
        int l, r, d; cin >> l >> r >> d;
        ops[i] = {l,r,d}; 
    }
    for (int i = 0; i < k; i++) {
        int x, y; cin >> x >> y;
        pre[x]++;
        pre[y+1]--;
    }
    //get number of queries
    for (int i = 1; i <= m; i++) {
        pre[i] += pre[i-1];
    }
    for (int i = 1; i <= m; i++) {
        Operation op = ops[i];
        agg[op.l] += op.d * pre[i];
        agg[op.r+1] -= op.d * pre[i];
    }
    for (int i = 1; i <= n; i++) {
        agg[i] += agg[i-1];
    }
    //get final array
    for (int i = 1; i <= n; i++) {
        A[i] += agg[i];
    }
    //output
    for (int i = 1; i <= n; i++) {
        cout << A[i] << ' ';
    }


    return 0;
}
	

