const int M = 1e9+7;
int mult(int a, int b) {
    return a = (1LL*a*b) % M;
}
int madd(int& a, int b) {
    return a = (a+b) % M;
}
int msub(int& a, int b) {
    return a = (a-b+M) % M;
}
int modexp(int a, int b) {
    int res = 1;
    while (b) {
        if (b&1) mult(res,a);
        mult(a,a);
        b >>= 1;
    }
    return res;
}
int inverse(int a) {
    return modexp(a,M-2);
}
