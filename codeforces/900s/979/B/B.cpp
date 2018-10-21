#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <set>
using namespace std;
typedef long long ll;

const int maxn = 100005;
int n, strsz;
int ribbon[3][maxn]; //ints from [0,52)
string winner[3] = {"Kuro","Shiro","Katie"};
int numOcc[3][52]; 

int charToInt(char c) {
    if ('a' <= c && c <= 'z') return c-'a';
    else if ('A' <= c && c <= 'Z') return c-'A'+26;
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    //get input
    cin >> n;
    for (int i = 0; i < 3; i++) {
        string s; cin >> s;
        strsz = s.size();
        for (int j = 0; j < s.size(); j++) {
            ribbon[i][j] = charToInt(s[j]);
            numOcc[i][charToInt(s[j])]++;
        }
    }
    //try to compute max, try each letter 0-51
    set<int> winners;
    int maxBeauty = 0;
    for (int i = 0; i < 3; i++) {
        for (int let = 0; let < 52; let++) {
            int tryBeauty = min(strsz,numOcc[i][let]+n);
            if (n == 1 && numOcc[i][let]+n > strsz) {
                tryBeauty--;
            }
            if (tryBeauty > maxBeauty) {
                maxBeauty = tryBeauty;
                winners = {i};
            }
            else if (tryBeauty == maxBeauty) {
                winners.insert(i);
            }    
        }
    }

    //output
    if (winners.size() == 1) {
        cout << winner[*winners.begin()] << '\n';
    }
    else {
        cout << "Draw\n";
    }


    return 0;
}
	

