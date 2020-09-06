struct Fenwick
{
    int n;
    vector<int> bit;
    Fenwick(int n_) {
        n = n_;
        bit.resize(n+1,0);
    }
    void add(int i, int x) {
        for (; i <= n; i += i & (-i))
            bit[i] += x;
    }

    int sum(int i) {
        int r = 0;
        for (; i; i -= i & (-i)) {
            r += bit[i];
        }
        return r;
    }
};
