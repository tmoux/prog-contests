struct Sparse
{
    //sparse table data structure for max
    static const int mk = 15; //change this number based on bounds
    int* tb[mk];
    static inline int lg(int x) { return 32 - __builtin_clz(x) - 1; }
    Sparse(int *a, int n) {
        for (int i = 0; i < mk; i++) {
            tb[i] = new int[n];
        }
        for (int i = 0; i < n; i++) tb[0][i] = a[i];
        for (int k = 1; k <= lg(n); k++) {
            for (int i = 0; i < n; i++) {
                int nx = i + (1<<(k-1));
                if (nx < n) tb[k][i] = max(tb[k-1][i],tb[k-1][nx]);
                else tb[k][i] = tb[k-1][i];
            }
        }
    }
    int getmax(int l, int r) {
        int g = lg(r-l+1);
        return max(tb[g][l],tb[g][r-(1<<g)+1]);
    }
};
