#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 100005;
int n, m; 
int A[maxn];

void update(int a, int b) {
    A[a] = b;
}

void query(int a) {
    int cnt = 1;
    while (a + A[a] <= n) {
        cnt++;
        a += A[a];
    }
    cout << a << ' ' << cnt << '\n';
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
    }
    while (m--) {
        int t; cin >> t;
        if (t == 0) {
            int a, b; cin >> a >> b;
            update(a,b);
        }
        else {
            int a; cin >> a;
            query(a);
        }
    }


    return 0;
}
	

