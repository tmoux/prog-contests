using namespace std;

#include <bits/stdc++.h>
constexpr int N = 10;
constexpr int a[] = {1,5,10,15,20,25,30,35,40,45};
void print_num(int i) {
    cout << i << '\n';
}
constexpr int get_item(int i) {
    return a[i];
}

constexpr int max(int a, int b) {
    return a<b?b:a;
}

constexpr int lis(int i);
constexpr int r(int i, int j) { //j < i
    if (j < 0) return 1;
    return max(r(i,j-1),get_item(j) < get_item(i) ? lis(j) + 1 : 0);
}

constexpr int lis(int i) { //return length of LIS ending at i
    if (i < 1) return 1;
    return r(i,i-1);
}

constexpr int gmax(int i) {
    if (i < 2) return lis(i);
    return max(lis(i),lis(i-1));
}

constexpr void pr(int i, int cur) {
    if (i < 0) return;
    if (!(lis(i) < cur) && !(lis(i) > cur)) {
        pr(i-1,cur-1);
        print_num(get_item(i));
    }
    else {
        pr(i-1,cur);
    }
}

int main()
{
    print_num(gmax(N-1));
    pr(N-1,gmax(N-1));    
}

