#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 1005;
int r, c, a, b;

int grid[maxn][maxn];
int grid2[maxn][maxn];

int freq[26];
int maxans[26];

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> c >> r >> b >> a;
    for (int i = 0; i < r; i++) {
        string s; cin >> s;
        for (int j = 0; j < c; j++) {
            grid[i][j] = s[j]-'a';
            grid2[j][i] = s[j]-'a';
        }
    }

    for (int i = 0; i + a <= r; i++) {
        //rows from [i,i+a]
        memset(freq,0,sizeof(freq));
        for (int j = i; j < i + a; j++) {
            for (int k = 0; k < b; k++) {
                freq[grid[j][k]]++;    
            }
        }
        for (int i = 0; i < 26; i++) {
            maxans[i] = max(maxans[i],freq[i]);
        }
        for (int col = b; col < c; col++) {
            //add col, remove col-b
            for (int j = i; j < i + a; j++) {
                freq[grid[j][col]]++;
                freq[grid[j][col-b]]--;
            }
            for (int i = 0; i < 26; i++) {
                maxans[i] = max(maxans[i],freq[i]);
            }
        }
    }
   
    //2nd pass
    swap(r,c);
    swap(a,b);
    for (int i = 0; i <= r - a; i++) {
        //rows from [i,i+a]
        memset(freq,0,sizeof(freq));
        for (int j = i; j < i + a; j++) {
            for (int k = 0; k < b; k++) {
                freq[grid2[j][k]]++;    
            }
        }
        for (int i = 0; i < 26; i++) {
            maxans[i] = max(maxans[i],freq[i]);
        }
        for (int col = b; col < c; col++) {
            //add col, remove col-b
            for (int j = i; j < i + a; j++) {
                freq[grid2[j][col]]++;
                freq[grid2[j][col-b]]--;
            }
            for (int i = 0; i < 26; i++) {
                maxans[i] = max(maxans[i],freq[i]);
            }
        }
    }

    for (int i = 0; i < 26; i++) {
        cout << maxans[i] << '\n';
    }

    /*
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cout << grid2[i][j] << ' ';
        }
        cout << '\n';
    }
    */
    return 0;
}
	

