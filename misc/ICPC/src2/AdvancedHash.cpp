ll base1[MX], base2[MX];



struct hsh  {
    ll base, p1, p2;

    ll val1, val2;
    ll inv1, inv2;

		vl val1s, val2s;

		vl inVal1s, inVal2s;

	ll modExp(ll power, ll prime) {
        if (power == 0) {
            return 1;
        } else {
            ll cur = modExp(power / 2, prime); cur = cur * cur; cur = cur % prime;
            if (power % 2 == 1) cur = cur * base;
            cur = cur % prime;
            return cur;
        }
    }

    hsh() {
    }


    hsh(ll b, string S) {
        p1 = 1000000007;
        p2 = 1000000009;
        base = b;
        val1 = 0;
        val2 = 0;

        inv2 = modExp(p2-2, p2);
        inv1 = modExp(p1-2, p1);
				val1s.pb(0); val2s.pb(0);
        F0R(i, sz(S)) {
            push_back(S[i] - 'a');
        }

    }

    void push_back(ll v) {
        val1 *= base;
        val1 %= p1;
        val1 += v;
        val1 %= p1;
        val2 *= base;
        val2 %= p2;
        val2 += v;
        val2 %= p2;

		val1s.pb(val1);
		val2s.pb(val2);
    }


		pl get(int L, int R) {
			ll A = (val1s[R+1] - (val1s[L] * base1[R-L+1]) % p1 + p1) % p1;
			ll B = (val2s[R+1] - (val2s[L] * base2[R-L+1]) % p2 + p2) % p2;
			return {A, B};
		}



};

  int base = uniform_int_distribution<int>(1000, MOD-2)(rng);

	base1[0] = 1; base2[0] = 1;
	FOR(i, 1, MX) {
		base1[i] = base1[i-1] * base; baseInv1[i] %= MOD;
		base2[i] = base2[i-1] * base; baseInv2[i] %= (MOD+2);
	}
