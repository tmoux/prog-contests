#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int ask(int c, int d) {
    printf("? %d %d\n",c,d);
    fflush(stdout);
    int i; cin >> i;
    assert(-1 <= i && i <= 1);
    return i;
}

void answer(int a, int b) {
    printf("! %d %d\n",a,b);
    fflush(stdout);
    exit(0);
}

int main()
{
    int c = 0, d = 0;
    int curr = ask(0,0);
    for (int k = 29; k >= 0; k--) {
        int c1 = ask(c^(1<<k),d);
        int c2 = ask(c,d^(1<<k));
        if (c1 == 1 && c2 == -1) {

        }
        else if (c1 == -1 && c2 == 1) {
            //must be (1,1)
            c |= (1<<k);
            d |= (1<<k);
        }
        else {
            if (curr == 1) {
                c |= (1<<k);
                curr = c1;    
            }
            else {
                d |= (1<<k);
                curr = c1;
            }
        }
    }
    answer(c,d);

    return 0;
}

