#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    printf("%d %d %d\n",1,n%3==0?1:2,n-(n%3==0?2:3));

    return 0;
}

