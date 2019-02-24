#include "Annalib.h"
#include <vector>
#include <string>

void Anna(int N, long long X, int K, int P[]) {
    std::vector<int> blocked(N,-1);
    std::string ans;
    for (int i = 0; i < K; i++) {
        blocked[P[i]] = 0;
    }
    int pos = 0;
    for (int i = 0; i < N; i += 3) {
        int cnt = (blocked[i] == 0) + (blocked[i+1] == 0) + (blocked[i+2] == 0);
        if (cnt > 1 || (X >> pos) == 0) {
            ans += "000";
        }
        else if (cnt == 1) {
            if (blocked[i] == 0) {
                if (!(1 & (X>>pos))) {
                    ans += "001";    
                }
                else {
                    ans += "010";
                }
                pos++;
            }
            else if (blocked[i+1] == 0) {
                if (!(1 & (X>>pos))) {
                    ans += "001";
                    pos++;
                }
                else {
                    pos++;
                    if (!(1 & (X>>pos))) {
                        ans += "100";
                    }
                    else {
                        ans += "101";
                    }
                    pos++;
                }
            }
            else {
                if (!(1 & (X>>pos))) {
                    ans += "110";
                }
                else {
                    ans += "010";
                }
                pos++;
            }
        }
        else {
            bool a = 1 & (X>>pos);
            bool b = 1 & (X>>(pos+1));
            int r = 2*a+b;
            if (r == 0) {
                ans += "011";
            }
            else if (r == 1) {
                ans += "111";
            }
            else if (r == 2) {
                ans += "100";
            }
            else {
                ans += "101";
            }
            pos += 2;        
        }
    }
    for (int i = 0; i < N; i++) {
        Set(i,ans[i]=='0'?0:1);            
    }
}
