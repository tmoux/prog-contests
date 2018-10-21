#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <map>
using namespace std;
typedef long long ll;

const int maxn = 200005;
int k;
int A[maxn];
map<int,pair<int,int>> mp;

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> k;
    for (int i = 0; i < k; i++) {
        int ni; cin >> ni;
        int sum = 0;
        for (int j = 0; j < ni; j++) {
            cin >> A[j];
            sum += A[j];
        }
        for (int j = 0; j < ni; j++) {
            int nxtsum = sum - A[j];
            auto it = mp.find(nxtsum);
            if (it != mp.end() && it->second.first != i+1) {
                cout << "YES\n";
                cout << it->second.first << ' ' << it->second.second << '\n';
                cout << (i+1) << ' ' << (j + 1) << '\n';
                return 0;
            }
            else {
                mp[nxtsum] = {i+1,j+1};
            }
        }
    }
    cout << "NO\n";
    


    return 0;
}
	

