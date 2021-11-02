const ll identity = 0;
const ll SZ = 131072;

ll sum[2*SZ], lazy[2*SZ];

ll combine(ll A, ll B) {
    return A+B;
}

ll combineUpd(ll A, ll B) {
    return A+B;
}

void push(int index, ll L, ll R) {
    sum[index] = combineUpd(sum[index], lazy[index]);
    if (L != R) lazy[2*index] = combineUpd(lazy[2*index], lazy[index]), lazy[2*index+1] = combineUpd(lazy[2*index+1], lazy[index]);
    lazy[index] = identity;
}

void pull(int index) {
    sum[index] = combine(sum[2*index], sum[2*index+1]);
}

bool checkCondition(int index) {
    //FILL THIS IN
}

ll query(int lo = 0, int hi = SZ-1, int index = 1, ll L = 0, ll R = SZ-1) { //returns first node satisfying con
    push(index, L, R);
    if (lo > R || L > hi) return -1;
    bool condition = checkCondition(index);
    if (L == R) {
        return (condition ? L : -1);
    }
    int M = (L+R) / 2;
    if (checkCondition(2*index+1)) {
        return query(lo, hi, 2*index+1, M+1, R);
    }
    return query(lo, hi, 2*index, L, M); 
}

void update(int lo, int hi, ll increase, int index = 1, ll L = 0, ll R = SZ-1) {
    push(index, L, R);
    if (hi < L || R < lo) return;
    if (lo <= L && R <= hi) {
        lazy[index] = increase;
        push(index, L, R);
        return;
    }

    int M = (L+R) / 2;
    update(lo, hi, increase, 2*index, L, M); update(lo, hi, increase, 2*index+1, M+1, R);
    pull(index);
}
