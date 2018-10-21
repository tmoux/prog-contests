#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 100005;
int n, A[maxn], dp[maxn], d[maxn];
vector<int> divs[maxn];

void getdivs(int i, vector<int>& vec) {
    for (int j = 2; j*j <= i; j++) {
        if (i % j == 0) {
            vec.push_back(j);
            vec.push_back(i/j);
        }
    }   
    vec.push_back(i);
}

int main()
{
    scanf("%d",&n);
    for (int i = 0; i < n; i++) {
        scanf("%d",A+i);
    }
    if (n == 1 && A[0] == 1) {
        cout << 1 << '\n';
        return 0;
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        getdivs(A[i],divs[A[i]]);
        for (int j: divs[A[i]]) {
            dp[i] = max(dp[i],d[j]+1);
        }
        for (int j: divs[A[i]]) {
            d[j] = max(d[j],dp[i]);
        }
        ans = max(ans,dp[i]);
    }
    printf("%d\n",ans);
    /*
    for (int i = 0; i < n; i++) {
        cout << A[i] << ' ' << dp[i] << '\n'; 
    }
    */
    return 0;
}
	

