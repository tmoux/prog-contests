#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstring>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

const int maxn = 100005;
const int INF = 999999;
int n, k;
int arr[maxn];
int key[256];
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    memset(key,-1,sizeof(key));
    for (int i = 0; i < n; i++) {
        //cout << "Number: " << arr[i] << '\n';
        if (key[arr[i]] != -1) {
            cout << key[arr[i]] << ' ';
            continue;
        }
        int lastUnfilled;
        bool isUpdate = true;
        for (int j = 0; j < k && arr[i]-j >= 0; j++) {
            int idx = arr[i]-j;
            if (key[idx] == -1 && isUpdate) {
                lastUnfilled = idx;
            }
            else if (key[idx] == idx) {
                //means it's a base key
                lastUnfilled = INF;
                for (int a = idx; a <= arr[i]; a++) {
                    key[a] = idx;
                }
                break;
            }
            else {
                isUpdate = false;
            }
        }
        //fill lastUnfilled to idx
        for (int j = lastUnfilled; j <= arr[i]; j++) {
            key[j] = lastUnfilled;
        }
        cout << key[arr[i]] << ' ';
    }
    cout << '\n';
    /*
    for (int i = 0; i < 256; i++) {
        if (key[i] != -1) {
            cout << i << ' ' << key[i] << '\n';
        }
    }
    */
	

    return 0;
}
	

