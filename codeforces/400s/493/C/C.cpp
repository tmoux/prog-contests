#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int m; cin >> m;
    vector<int> b(m);
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }
    
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());

    int maxscore = -999999999;
    pair<int,int> p = {0,0};
    for (int i = 0; i < n; i++) {
        auto it = upper_bound(b.begin(),b.end(),a[i]-1);
        int a1 = i, a2 = n-a1;
        int b1 = distance(b.begin(),it), b2 = m-b1;

        //cout << a[i] << ": " << a1 << ' ' << a2 << ", " << b1 << ' ' << b2 << '\n';

        int score1 = a1*2+3*a2;
        int score2 = b1*2+3*b2;
        if (score1-score2 > maxscore || (score1-score2 == maxscore && score1 > p.first)) {
            maxscore = score1-score2;
            p = {score1,score2};
        }
    }

     for (int i = 0; i < m; i++) {
        auto it = upper_bound(a.begin(),a.end(),b[i]+1);
        int a1 = distance(a.begin(),it), a2 = n-a1;
        int b1 = i+1, b2 = m - b1;

        //cout << b[i] << ": " << a1 << ' ' << a2 << ", " << b1 << ' ' << b2 << '\n';

        int score1 = a1*2+3*a2;
        int score2 = b1*2+3*b2;
        if (score1-score2 > maxscore || (score1-score2 == maxscore && score1 > p.first)) {
            maxscore = score1-score2;
            p = {score1,score2};
        }
    }

    //output
    printf("%d:%d\n",p.first,p.second);

    return 0;
}
	

