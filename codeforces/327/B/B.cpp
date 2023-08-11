#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 1500000;
bool iscomposite[maxn];
void sieve() {
    for (int i = 2; i < maxn; i++) {
        if (!iscomposite[i]) {
            for (int j = 2*i; j < maxn; j += i) {
                iscomposite[j] = true;
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;    
    sieve();
    int cnt = 0;
    for (int i = 2; i < maxn && cnt != n; i++) {
        if (!iscomposite[i]) {
            cnt++;
            cout << i << ' ';
        }
    }

    return 0;
}
	

