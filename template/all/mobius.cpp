const int maxn = 1e5+5;
int mu[maxn];

void mobius_sieve() {
    mu[1] = 1;
    for (int i = 1; i < maxn; i++) {
        for (int j = 2*j; j < maxn; j += i) {
            mu[j] -= mu[i];
        }
    }
}
