#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 205;
ll arr[maxn];
int nxt[maxn];
int pred[maxn];
int n;


int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (arr[j] == 2*arr[i] || (arr[i] % 3 == 0 && arr[j] == arr[i]/3)) {
                nxt[i] = j;
                pred[j]++;
                break;
            }
        }
    }
    int start = 0;
    for (int i = 0; i < n; i++) {
       //cout << i << ' ' << pred[i] << ' ' << start << '\n';
       if (pred[i] == 0) {
           start = i;
           break;
       }
    }
    //cout << start << '\n';
    for (int i = 0; i < n; i++) {
        cout << arr[start] << ' ';
        start = nxt[start];
    }


    return 0;
}
	

