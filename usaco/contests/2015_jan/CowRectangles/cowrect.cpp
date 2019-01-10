#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 505;
int N;
int pfxH[1005][1005], pfxG[1005][1005];
vector<pair<int,int>> pts;

int getPfx(int x1, int y1, int x2, int y2, int arr[1005][1005]) {
    return arr[x2][y2] - arr[x1-1][y2] - arr[x2][y1-1] + arr[x1-1][y1-1];            
}

int main()
{
    freopen("cowrect.in","r",stdin); freopen("cowrect.out","w",stdout);
    cin >> N;
    for (int i = 0; i < N; i++) {
        char c;
        int x, y; cin >> x >> y >> c;
        x++; y++;            
        if (c == 'H') {
            pts.push_back({x,y});
            pfxH[x][y]++;    
        }
        else if (c == 'G') {
            pfxG[x][y]++;
        }
    }
    //update prefixes
    for (int i = 1; i <= 1001; i++) {
        for (int j = 1; j <= 1001; j++) {
            pfxH[i][j] = pfxH[i][j] + pfxH[i-1][j] + pfxH[i][j-1] - pfxH[i-1][j-1];    
            pfxG[i][j] = pfxG[i][j] + pfxG[i-1][j] + pfxG[i][j-1] - pfxG[i-1][j-1];
        }
    }
    
    pair<int,int> best = {0,0};
    for (int i = 0; i < pts.size(); i++) {
        for (int j = i; j < pts.size(); j++) {
            auto p1 = pts[i]; 
            auto p2 = pts[j];
            int x1 = min(p1.first,p2.first);
            int x2 = max(p1.first,p2.first);
            int y1 = min(p1.second,p2.second);
            int y2 = max(p1.second,p2.second);
            int cnt = getPfx(x1,y1,x2,y2,pfxH);       
            if (getPfx(x1,y1,x2,y2,pfxG) > 0) continue;
            int lastIncrease = y2;
            while (y2 + 1 <= 1001 && getPfx(x1,y1,x2,y2+1,pfxG) == 0) {
                int ncnt = getPfx(x1,y1,x2,y2+1,pfxH);
                if (ncnt > cnt) {
                    cnt = ncnt;
                    lastIncrease = y2 + 1;
                }
                y2++;
            }
            y2 = lastIncrease;
            
            lastIncrease = y1;
            while (y1 - 1 >= 1 && getPfx(x1,y1-1,x2,y2,pfxG) == 0) {
                int ncnt = getPfx(x1,y1-1,x2,y2,pfxH);
                if (ncnt > cnt) {
                    cnt = ncnt;
                    lastIncrease = y1 - 1;
                }
                y1--;
            }
            y1 = lastIncrease;
            int area = (x2-x1) * (y2-y1);

            //printf("Two points (%d,%d) and (%d,%d): (%d,%d), (%d,%d)\n",p1.first,p1.second,p2.first,p2.second,x1,y1,x2,y2);
            //printf("Cnt = %d, area = %d\n",cnt,area);
            if (cnt > best.first) {
                best = {cnt,area};    
            }
            else if (cnt == best.first) {
                best.second = min(best.second,area);
            }
        }
    }

    printf("%d\n%d\n",best.first,best.second);

    return 0;
}

