template<typename T>
struct Fenwick
{
    int n;
    vector<T> bit;
    Fenwick(int n_) {
        n = n_;
        bit.resize(n+1,0);
    }
    void add(int i, T x) {
        for (; i <= n; i += i & (-i))
            bit[i] += x;
    }

    T sum(int i) {
        T r = 0;
        for (; i; i -= i & (-i)) {
            r += bit[i];
        }
        return r;
    }
};
