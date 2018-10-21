#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

int n;
vector<string> words;
int pre[500];

int dp[305][305];

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    words.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> words[i];
    }
    pre[0] = words[0].size();
    for (int i = 1; i < n; i++) {
        pre[i] = pre[i-1] + words[i].size() + 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int dist = 0;
            for (int k = 0; k <= j - i - 1; k++) {
                if (words[i+k] == words[j+k]) {
                    dist++;
                }
                else break;
            }
            dp[i][dist]++;
        }
    }

    

     

    return 0;
}
	

