#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n;
string s;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> s;
    int sum1 = 0, sum2 = 0, space1 = 0, space2 = 0;
    for (int i = 0; i < n/2; i++) {
        if (s[i] == '?') space1++;
        else sum1 += s[i]-'0';
    }
    for (int i = n/2; i < n; i++) {
        if (s[i] == '?') space2++;
        else sum2 += s[i]-'0';
    }
    int turn = 0;
    while (space1 + space2 > 0) {
        if (turn == 0) {
            //try to unbalance
            if (sum1 == sum2) {
                if (space1 > 0 && space1 > space2) {
                    sum1 += 9;
                    space1--;
                }
                else {
                    sum2 += 9;
                    space2--;
                }
            }
            else if (sum1 > sum2) {
                if (space1 > 0) {
                    sum1 += 9;
                    space1--;
                }
                else {
                    space2--;
                }
            }
            else if (sum2 > sum1) {
                if (space2 > 0) {
                    sum2 += 9;
                    space2--;
                }
                else {
                    space1--;
                }
            }
        }
        else {
            if (sum1 == sum2) {
                if (space1 > 0 && space1 > space2) {
                    space1--;
                }
                else {
                    space2--;
                }
            }
            else if (sum1 < sum2) {
                if (space1 > 0) {
                    sum1 += min(9,sum2-sum1);
                    space1--;
                }
                else {
                    space2--;
                }
            }
            else if (sum1 > sum2) {
                if (space2 > 0) {
                    sum2 += min(9,sum1-sum2);
                    space2--;
                }
                else {
                    space1--;
                }
            }
        }
        //printf("sum1 = %d, sum2 = %d, space1 = %d, space2 = %d\n",sum1,sum2,space1,sum2);
        turn ^= 1;
    }
    cout << ((sum1 == sum2) ? "Bicarp" : "Monocarp") << '\n';
}

